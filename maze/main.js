var c = document.getElementById("canvas");
var ctx = c.getContext("2d");

class pos
{
	constructor(x=0, y=0) {
		this.x = x;
    	this.y = y;
	}
};

class Maze
{
	constructor(WIDTH = 0, HEIGHT = 0) {
		this.width = WIDTH;
		this.height = HEIGHT; 
		this.map = new Array(WIDTH * HEIGHT);
		this.current;

	}
	draw() {

	}
		void Create();
		
	private:
		bool CheckMaze(pos*, int);
		pos stack[10000];
		int d;
		pos current;
		int cnt;
};


var c_width = window.innerWidth * 0.8;
var c_height = window.innerHeight * 0.8;
var H = 20;
var W = 20;
var Left = c_width * 0.1;//window.innerWidth * 0.2;
var Right = c_width / 0.64 + 5;//window.innerWidth;
var Top = c_height * 0.2;//window.innerHeight * 0.2;
var Button = c_height / 0.8 + 5;//window.innerHeight;
var 

function resizeCanvas() {
	c.setAttribute(width, window.innerWidth * 0.8);
	c.setAttribute(height, window.innerHeight * 0.8);
	//c.style.width = window.innerWidth * 0.8 + "px";
	//c.style.height = window.innerHeight * 0.8 + "px";
	c.style.margin = window.innerHeight * 0.1 + "px " + window.innerWidth * 0.1 + "px";
	console.log("width: "+ window.innerWidth);
	console.log("height: "+ window.innerHeight);
	console.log(c.style.width);
}

function init() {
	window.addEventListener('resize', resizeCanvas, false);
	resizeCanvas();
	for(i = 0; i < H; i++)
		for(j = 0; j < W; j++) 
			maze[i*W+j] = 0;

}

function drawGrid() {

	var grid_width = (Right - Left) / W;
	var grid_height = (Button - Top) / H;
	console.log(Left);
	console.log(Right);
	for(i = 0; i <= H; i++) {
		ctx.beginPath();
		ctx.moveTo(Left-5, Top + grid_height * i);
		ctx.lineTo(Right+5, Top + grid_height * i);
		ctx.stroke();
		console.log("draw h: " + (Top + grid_height * i));
	}	
	for(i = 0; i <= W; i++) {
		ctx.beginPath();
		ctx.moveTo(Left + grid_width * i, Top);
		ctx.lineTo(Left + grid_width * i, Button);
		ctx.stroke();
		console.log("draw w: " + (Left + grid_width * i));
	}
}
*/
function draw() {
	ctx.lineWidth = 10;

	
	drawGrid();
	
}

//init()
draw()
