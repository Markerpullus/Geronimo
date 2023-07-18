import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float inByte = 0;

double topLeftLat = 39.874980;
double topLeftLong = -86.102092;
double botRightLat = 39.874584;
double botRightLong = -86.101650;

double x, y;

PImage img;

void setup () {
  // set the window size:
  size(660, 769);
  img = loadImage("satellite.png");

  // List all the available serial ports
  // if using Processing 2.1 or later, use Serial.printArray()
  println(Serial.list());

  // I know that the first port in the serial list on my Mac is always my
  // Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[2], 115200);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set initial background:
  background(0);
}

void draw () {
  image(img, 0, 0);
  circle((float)x, (float)y, 10);
}

int line = 0;
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null && line > 1) {
    // trim off any whitespace:
    inString = trim(inString);
    String[] coords = inString.split(", ");
    double lat = Double.parseDouble(coords[0]);
    double lon = Double.parseDouble(coords[1]);
    println(lat);
    println(lon);
    x = (lon - topLeftLong) / (botRightLong - topLeftLong) * 660;
    y = (lat - topLeftLat) / (botRightLat - topLeftLat) * 769;
  }
  line ++;
}

double convert (double coord) {
  double result;
  int a;
  if (coord > 0) {
    a = floor((float)coord / 100);
  } else {
    a = ceil((float)coord / 100);
  }
  
  double b = (coord - a * 100) / 60;
  result = a + b;
  
  return result;
}
