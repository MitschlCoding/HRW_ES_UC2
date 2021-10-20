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

//popup variables
const openPopupButtons = document.querySelectorAll("[data-popup-target]");
const closePopupButtons = document.querySelectorAll("[data-close-button]");
const overlay= document.getElementById('popupOverlay');

//popup event listeners
//listen to all open buttons
openPopupButtons.forEach(button => {
	button.addEventListener("click", () => {
		const popup = document.querySelector(button.dataset.popupTarget);
		openPopup(popup);
	})
})
//listen to all close buttons
closePopupButtons.forEach(button => {
	button.addEventListener("click", () => {
		const popup = button.closest(".addPopup");
		closePopup(popup);
	})
})
//open a popup window
function openPopup(popup){
	if(popup == null) return;
	popup.classList.add("active");
	overlay.classList.add("active");
}
//close a popup window
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
function addDevice() {
	//if its an led send the data to backend
	if(document.getElementById("selectDevice").value == "LED"){
		let pin = document.getElementById("ledPinInput1").value;
		if(pin != ""){
			//send post request, that adds a LED
			fetch("/post/add/LED", {
				method: "POST",
				body: deviceID.toString() + "," + pin.toString()
			}).then(res => {
				console.log("Post request complete! response:" + res);
			});
			//add controll element to controll section
			let controlls = document.getElementsByClassName("controlls");
			let ledDiv = document.createElement("div");
			ledDiv.className = "centered";
			let ledText = document.createElement("p");
			ledText.className = "ledParagraph";
			ledText.innerText = "LED - " + "ID:";
			let ledID = document.createElement("p");
			ledID.className = "ledID";
			ledID.innerText = deviceID.toString();
			let ledButton = document.createElement("button");
			ledButton.className = "button";
			ledButton.id = "ledChangeState" + deviceID.toString();
			ledButton.setAttribute("onClick", "changeLEDState(this)");
			ledButton.innerText = "Turn On/Off";
			controlls[0].appendChild(ledDiv);
			ledDiv.appendChild(ledText);
			ledDiv.appendChild(ledID);
			ledDiv.appendChild(ledButton);
			//increment deviceID for next device
			deviceID++;
		}
	}
	//if its a motor send the data to backend
	if(document.getElementById("selectDevice").value == "Motor"){
		let pin1 = document.getElementById("motorPinInput1").value;
		let pin2 = document.getElementById("motorPinInput2").value;
		let pin3 = document.getElementById("motorPinInput3").value;
		let pin4 = document.getElementById("motorPinInput4").value;
		//send a post request, that adds a device to the backend
		if(pin1 != "" && pin2 != "" && pin3 != "" && pin4 != ""){
			fetch("/post/add/Motor", {
				method: "POST",
				body: deviceID.toString() + "," + pin1.toString() + "," + pin2.toString() + "," + pin3.toString() + "," + pin4.toString()
			}).then(res => {
				console.log("Post request complete! response:" + res);
			});
			//add controll element to controll section
			let controlls = document.getElementsByClassName("controlls");
			let motorDiv = document.createElement("div");
			motorDiv.className = "centered";
			let motorText = document.createElement("p");
			motorText.className = "motorParagraph";
			motorText.innerText = "Motor - " + "ID:";
			let motorID = document.createElement("p");
			motorID.className = "motorID";
			motorID.innerText = deviceID.toString();
			let motorStepInput = document.createElement("input");
			motorStepInput.className = "motorStepInput";
			let motorButton = document.createElement("button");
			motorButton.className = "button";
			motorButton.id = "motorChangeState" + deviceID.toString();
			motorButton.setAttribute("onClick", "changeMotorState(this)");
			motorButton.innerText = "Send";
			controlls[0].appendChild(motorDiv);
			motorDiv.appendChild(motorText);
			motorDiv.appendChild(motorID);
			motorDiv.appendChild(motorStepInput);
			motorDiv.appendChild(motorButton);

			//increment deviceID for next device
			deviceID++;
		}
	}
	//close popup window
	let popupAdd = document.getElementById("addDevice").closest(".addPopup");
	closePopup(popupAdd);
}

//sends a POST request to the server, that changes the state of a LED
function changeLEDState(_button) {
	let id = _button.closest("div").children[1].innerText;
	fetch("/post/change/LED", {
		method: "POST",
		body: id
	}).then(res => {
		console.log("Post request complete! response:", res)
	});
}

//sends a Post request to the server, that changes the state of a Motor
function changeMotorState(_button) {
	let id = _button.closest("div").children[1].innerText;
	let steps = _button.closest("div").children[2].value;
	fetch("/post/change/Motor", {
		method: "POST",
		body: id + "," + steps.toString()
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
		input.className = "pinInput";
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
		input1.className = "pinInput";
		input1.id = "motorPinInput1";	
		let div2 = document.createElement("div");
		div2.className = "centered";
		let input2 = document.createElement("input");
		input2.className = "pinInput";
		input2.id = "motorPinInput2";
		let div3 = document.createElement("div");
		div3.className = "centered";
		let input3 = document.createElement("input");
		input3.className = "pinInput";
		input3.id = "motorPinInput3";
		let div4 = document.createElement("div");
		div4.className = "centered";
		let input4 = document.createElement("input");
		input4.className = "pinInput";
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
