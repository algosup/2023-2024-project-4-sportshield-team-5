/* This file aims to be used as a testing tool to ensure the correct working of SportShield using GPRS and 2G network.
   It will be hosted on a server and will be used to simulate the behaviour of the SportShield API from the client point of view.
   Additionally, it will log all the requests made to the server in a file called testing.log to keep track of the requests and testing made.
*/

// ---------------------------- IMPORTS ----------------------------
import express, { Request, Response } from "express";
import { writeFile, readdir, appendFile } from "fs";

// ---------------------------- INITIALISATION ----------------------------
// Create express app and listener
const app = express();
const PORT = 3000; // Port on which we are going to listen the inputs

// Interface of payload for notification
interface GenericPayload {
  latitude: String;
  longitude: String;
  battery: Number;
}

// Interface of payload for device linking
interface DevicePayload {
  BLEAddress: String;
}

checkLogFile();

// ---------------------------- MIDDLEWARES ----------------------------
app.use(express.json()); // Used to parse JSON bodies
app.use(express.urlencoded({ extended: true })); // Used to parse URL-encoded bodies

// ---------------------------- ROUTES ----------------------------

// Route used to link your device to the SportShield API and send data to the phone associated with the lock
app.get(
  "/deviceLinking/:BLEAddress",
  (req: Request<{ BLEAddress: string }>, res: Response) => {
    const BLEAddress: String = req.params.BLEAddress;
    const payload: DevicePayload = req.body;

    console.log(`Device linked - BLE Address: ${BLEAddress}`);
    console.log(payload);

    logToFile(`Device linked - BLE Address: ${BLEAddress}`);
    logToFile(`Received payload: ${JSON.stringify(payload)}`);

    res.status(200).send("Device linked");
  }
);

// Route used to unlink your device from the SportShield API and not send data to the phone associated with the lock anymore
app.get("/deviceUnlinking/:BLEAddress", (req, res) => {
  const BLEAddress: String = req.params.BLEAddress;

  console.log(`Device unlinked - BLE Address: ${BLEAddress}`);

  logToFile(`Device unlinked - BLE Address: ${BLEAddress}`);

  res.status(200).send("Device unlinked");
});

// Route for movement detection
app.get(
  "/sendNotification/:BLEAddress",
  (req: Request<{ BLEAddress: string }, {}, GenericPayload>, res: Response) => {
    const BLEAddress: String = req.params.BLEAddress;
    const payload: GenericPayload = req.body;

    console.log(`Movement notification sent - BLE Address: ${BLEAddress}`);
    console.log(payload);

    logToFile(`Movement notification sent - BLE Address: ${BLEAddress}`);
    logToFile(`Received payload: ${JSON.stringify(payload)}`);

    res.status(200).send("Notification sent");
  }
);

// Route used to send the coordinates and battery level of the device at regular intervals
app.get(
  "/updateCoordinate/:BLEAddress",
  (req: Request<{ BLEAddress: string }, {}, GenericPayload>, res: Response) => {
    const BLEAddress: String = req.params.BLEAddress;
    const payload: GenericPayload = req.body;
    console.log(`Update of the coordinate - BLE Address: ${BLEAddress}`);
    console.log(payload);

    logToFile(`Update of the coordinate - BLE Address: ${BLEAddress}`);
    logToFile(`Received payload: ${JSON.stringify(payload)}`);

    res.status(200).send("Coordinate updated");
  }
);

// Route used to notify a wrong NFC tag has been detected by the reader
app.get("/NFCUnlockAttempt/:BLEAddress", (req, res) => {
  const BLEAddress: String = req.params.BLEAddress;

  console.log(`NFC unlock attempt - BLE Address: ${BLEAddress}`);

  logToFile(`NFC unlock attempt - BLE Address: ${BLEAddress}`);

  res.status(200).send("NFC unlock attempt");
});

// ---------------------------- SERVER LAUNCH ----------------------------
app.listen(PORT, () => {
  console.log(`Server is running on port 3000`);
});

// ---------------------------- FUNCTIONS ----------------------------

/**
 * Verify if the log file already exists, if not, we create it and initialize it
 */
function checkLogFile() {
  readdir(".", (err, files) => {
    if (!files.includes("testing.log")) {
      writeFile("testing.log", "Logs of SportShield testing\n\n", (err) => {
        if (err) {
          console.error(err);
          return;
        }
        console.log("Log file has been created");
      });
    }
  });
}

/**
 * @param {string} message - The message to be logged in the .log file
 */
function logToFile(message: string) {
  appendFile(
    "testing.log",
    `${new Date().toLocaleString()} - ${message}\n`,
    (err) => {
      if (err) {
        console.error(err);
        return;
      }
    }
  );
}
