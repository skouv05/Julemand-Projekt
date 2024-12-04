const myp=document.getElementById('test1');
myp.innerHTML='Button';
//retrieve json from server using fetch every 500 ms
//https://stackoverflow.com/questions/72058563/web-based-timer-application-using-window-setinterval-method-in-javascript-does-n
//https://www.youtube.com/watch?v=C3dfjyft_m4
let timer = setInterval(update, 500);
function update() {
	fetch('/button')
		.then(response => response.json())
		.then(data => {
			if(data.button=='1') {
				//højttaler skal give wav fil besked
				//tag billede med phone
				//send til server
				myp.innerHtml=data.button; // for now
				playspeak();
				
				SendImageServer(TakePhoto());
			}
		})
}
function playspeak() {
	//wav play - hvordan får vi audio fil med ud?
	//var audio = new Audio('audio_file.mp3');
	//audio.play();

}
function TakePhoto() {
	//photo snapshot
    let canvas = document.createElement('canvas');
let video = document.getElementById('video');

canvas.width = 1920;
canvas.height = 1080;

let ctx = canvas.getContext('2d');
ctx.drawImage( video, 0, 0, canvas.width, canvas.height );

let image = canvas.toDataURL('image/jpeg');
console.log(image);
return image;
}
function SendImageServer(image) {
	fetch('helseviden.dk/upload.php', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json',
		},
		body: JSON.stringify({ image: image })
	})
	.then(response => response.json())
	.then(data => {
		console.log('Success:', data);
	})
	.catch((error) => {
		console.error('Error:', error);
	});

}

const constraints = {
    audio: false,
    video: { width: 1280, height: 720 },
  };
  
  navigator.mediaDevices
    .getUserMedia(constraints)
    .then((mediaStream) => {
      const video = document.querySelector("video");
      video.srcObject = mediaStream;
      video.onloadedmetadata = () => {
        video.play();
      };
    })
    .catch((err) => {
      // always check for errors at the end.
      console.error(`${err.name}: ${err.message}`);
    });