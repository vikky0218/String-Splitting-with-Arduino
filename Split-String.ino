const int maxStringLength = 256;
String head[20];
String body[30];

// Default values for initial setup
String logType = "null";
String NoOfSensor = "null";
String deviceName = "Logger";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Check if there is data available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming data until a newline character is encountered
    String dataS = Serial.readStringUntil('\n');

    // Clear the arrays to store new data
    for (int i = 0; i < 20; i++) {
      head[i] = "";
    }
    for (int i = 0; i < 30; i++) {
      body[i] = "";
    }

    // Split the incoming data into segments using the '_' delimiter
    int headCount = splitString(dataS, '_', head);

    // Extract the first segment, which is a command identifier
    String con = head[0];

    // Check the command identifier for further actions
    if (con.equals("UNO")) {
      // If UNO command is received, update device information
      logType = head[1];
      NoOfSensor = head[2];
      deviceName = head[3];
    } else if (con.equals(deviceName)) {
      // If the command identifier matches the device name, process the command
      String cmd = head[1];
      String unit = head[2];

      // Check the command type
      if (cmd.equals("VALUES")) {
        // If the command is VALUES, handle specific cases based on logType and NoOfSensor
        if (logType.equals("Temperature")) {
          if (NoOfSensor.equals("1")) {
            // Split the last segment of the head array to extract temperature values
            splitString(head[headCount - 1], ' ', body);
            String t1 = body[1];
            String date = body[3];
            String time = body[4];
          }
        }
      }
    }
  }
}

// Function to split a string into an array of strings using a specified delimiter
int splitString(String input, char delimiter, String output[]) {
  int count = 0;
  int lastIndex = 0;
  int length = input.length();

  // Iterate through the characters of the input string
  for (int i = 0; i < length; i++) {
    // Check for the delimiter character
    if (input[i] == delimiter) {
      // Extract the substring between the last index and the current delimiter
      output[count] = input.substring(lastIndex, i);
      lastIndex = i + 1;
      count++;
    }
  }

  // Extract the remaining substring after the last delimiter
  output[count] = input.substring(lastIndex);

  // Return the total count of segments in the output array
  return count + 1;
}
