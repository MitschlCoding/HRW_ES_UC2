//video constraints
let constraints = { video: { width: window.outerWidth / 2 }};
let video = document.querySelector('video');
let canvas = document.querySelector('canvas');
let context = canvas.getContext('2d');
let w, h, ratio;
let position = 0;
let focus = 0;

//push the camera input into the liveVideo
navigator.mediaDevices.getUserMedia(constraints)
	.then(function (mediaStream) {
		video.srcObject = mediaStream;
		video.onloadedmetadata = function (e) {
			video.play();
		};
		//The following 2 lines will change the focus, once we use a device that is capable of doing so
		//track = mediaStream.getVideoTracks()[0];
		//track.applyConstraints(advanced: [{focusMode: "manual", focusDistance: "max"}]);
	})
	.catch(function (err) {
		console.log(err.name + ": " + err.message);
	});

//when the video is loaded, the canvas is calculated
video.addEventListener('loadedmetadata', function () {
	ratio = video.videoWidth / video.videoHeight;
	w = video.videoWidth;
	h = parseInt(w / ratio, 10);
	canvas.width = w;
	canvas.height = h;
	context.fillStyle = "black";
	context.fillRect(0, 0, w, h);
}, false);

//draw image onto canvas on button press
function snap() {
	context.drawImage(video, 0, 0, w, h);
}

//sends a POST request to the server, that adds a LED to the pin in the value box
function addLED() {
	let pin = document.getElementById("pinNumberLED").value;
	fetch("/post/add/LED", {
		method: "POST",
		body: pin.toString()
	}).then(res => {
		console.log("Post request complete! response:", res);
	});
}

//sends a POST request to the server, that changes the state of an LED
//TODO!!!!! make it be specific to the LED
function turnLEDOn() {
	let state = document.getElementById("turnLEDOnState").value;
	fetch("/post/change/LED", {
		method: "POST",
		body: state.toString()
	}).then(res => {
		console.log("Post request complete! response:", res)
	});
}