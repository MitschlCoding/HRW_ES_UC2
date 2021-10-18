//id for devices
let deviceID = 0;

//video constraints
let constraints = { video: { width: window.outerWidth / 2 }};
let video = document.querySelector('video');
let canvas = document.querySelector('canvas');
let context = canvas.getContext('2d');
let w, h, ratio;
let position = 0;
let focus = 0;

//popup
const openPopupButtons = document.querySelectorAll("[data-popup-target]");
const closePopupButtons = document.querySelectorAll("[data-close-button]");
const overlay= document.getElementById('popupOverlay');

//popup event listeners
openPopupButtons.forEach(button => {
	button.addEventListener("click", () => {
		const popup = document.querySelector(button.dataset.popupTarget);
		openPopup(popup);
	})
})

closePopupButtons.forEach(button => {
	button.addEventListener("click", () => {
		const popup = button.closest(".addPopup");
		closePopup(popup);
	})
})

function openPopup(popup){
	if(popup == null) return;
	popup.classList.add("active");
	overlay.classList.add("active");
}

function closePopup(popup){
	if(popup == null) return;
	popup.classList.remove("active");
	overlay.classList.remove("active");
}


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

//changes the displayed number of Pins based on the selected device
function displayPinInputs(){
	let pinInputs = document.getElementById("devicePins");
	if(document.getElementById("selectDevice").value == "LED"){
		//remove all pin inputs then add one new one for the LED
		var child = pinInputs.lastElementChild;
		while(child){
			pinInputs.removeChild(child);
			child = pinInputs.lastElementChild;
		}
		let device = document.createElement("div");
		device.className = "centered";
		let input = document.createElement("input");
		input.id = "ledPinInput1";
		pinInputs.appendChild(device);
		device.appendChild(input);
	} else if(document.getElementById("selectDevice").value == "Motor"){
		//remove all pin inputs then add 4 new one for a motor
		var child = pinInputs.lastElementChild;
		while(child){
			pinInputs.removeChild(child);
			child = pinInputs.lastElementChild;
		}
		let device = document.createElement("div");
		device.className = "block";
		let div1 = document.createElement("div");
		div1.className = "centered";
		let input1 = document.createElement("input");
		input1.id = "motorPinInput1";	
		let div2 = document.createElement("div");
		div2.className = "centered";
		let input2 = document.createElement("input");
		input2.id = "motorPinInput2";
		let div3 = document.createElement("div");
		div3.className = "centered";
		let input3 = document.createElement("input");
		input3.id = "motorPinInput3";
		let div4 = document.createElement("div");
		div4.className = "centered";
		let input4 = document.createElement("input");
		input4.id = "motorPinInput4";
		pinInputs.appendChild(device);
		div1.appendChild(input1);
		div2.appendChild(input2);
		div3.appendChild(input3);
		div4.appendChild(input4);
		device.appendChild(div1);
		device.appendChild(div2);
		device.appendChild(div3);
		device.appendChild(div4);
	}
}