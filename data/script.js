let songIndex = 0;
let songList = [];

function sendCommand(command, index = null) {
    let url = `/${command}`;
    let options = {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
    };

    if (index !== null) {
        options.body = JSON.stringify({ index: index });
    }

    fetch(url, options)
        .then(response => {
            if (response.ok) {
                console.log(`Command ${command} sent successfully.`);
            } else {
                console.error(`Error sending command: ${response.statusText}`);
            }
        })
        .catch(error => console.error('Fetch error:', error));
}

function displayCurrentSong() {
    if (songList.length > 0) {
        const song = songList[songIndex];
        document.getElementById("songInfo").innerText = `Song ${songIndex + 1}: ${song[0]} - ${song[1]}`;
    } else {
        document.getElementById("songInfo").innerText = "No song data available";
    }
}

function fetchCueData() {
    fetch("/cue_data")
        .then(response => {
            if (!response.ok) throw new Error("Failed to fetch cue data");
            return response.json();
        })
        .then(data => {
            songList = data;
            if (songList.length > 0) {
                displayCurrentSong();
                fetchCurrentSongIndex();  // Get the current song index from server after loading song list
            }
        })
        .catch(error => console.error("Error fetching cue data:", error));
}

// Fetch current song index from server and update the display
function fetchCurrentSongIndex() {
    fetch("/current_song")
        .then(response => {
            if (!response.ok) throw new Error("Failed to fetch current song index");
            return response.json();
        })
        .then(data => {
            if (data && data.currentIndex !== undefined) {
                songIndex = data.currentIndex;  // Update songIndex based on server's current song
                displayCurrentSong();           // Display the current song based on updated index
            } else {
                console.warn("Invalid current song index data received");
            }
        })
        .catch(error => console.error("Error fetching current song index:", error));
}

function nextSong() {
    if (songList.length > 0) {
        songIndex = (songIndex + 1) % songList.length;
        displayCurrentSong();
        sendCommand("select_song", songIndex);
    }
}

function prevSong() {
    if (songList.length > 0) {
        songIndex = (songIndex - 1 + songList.length) % songList.length;
        displayCurrentSong();
        sendCommand("select_song", songIndex);
    }
}

window.onload = function() {
    fetchCueData();  // Load song list and then fetch the current song index from the server
};
