import processing.net.*;
Server myServer;
int robotX, robotY;
String received_value="0";

void setup() {
  size(900, 900);
  // Start server on port 5204
  myServer = new Server(this, 5204); 
}

void draw() {
    // Get the next available client
    Client thisClient = myServer.available();
    // If the client is not null, and says something, display what it said
    if (thisClient != null) {
       received_value = thisClient.readString();
        if (received_value != null) {
            println("received value is "  + received_value);
        }
    }
    
      translate(width / 2, height / 2); // Origin is now at (200, 200)

  // 2. Invert the Y-axis so positive goes up (optional but helpful for standard graphs)
  scale(1, -1); 

  String[] parts = received_value.split(",");
  //println("parts length" + parts.length);
  if(parts.length ==4)
  {
    robotX = Integer.parseInt(parts[2].trim());
    robotY = Integer.parseInt(parts[3].trim());
    
    
    print(parts[2]);
    print(" ");
    println(parts[3]);
  }
  
  
    
    
      // Draw the robot's current position as a point
  stroke(0, 0, 255); // Blue color for the point
  strokeWeight(5); // Make the point visible
  point(robotX, robotY); 

 

  // Keep the robot within the window boundaries
  robotX = constrain(robotX, 0, width);
 robotY = constrain(robotY, 0, height);
}
