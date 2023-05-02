<?php

$servername = "localhost";
$dbname ="pathavanesp32";
$username = "PATHAVAN";
$password ="TestingESP32@";

$api_key_value = "Testin32ESP@";
$api_key = $SENSORDATA =$LOCATIONDATA =$value1= $value2 = $value3=$reading_time = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
	$api_key = test_input($_POST["api_key"]);
	if($api_key == $api_key_value){
		$sensor = test_input($_POST["SENSORDATA"]);
		$location = test_input($_POST["LOCATIONDATA"]);
		$value1 = test_input($_POST["value1"]);
		$value2 = test_input($_POST["value2"]);
		$value3 = test_input($_POST["value3"]);

//create connection 
$conn = new mysqli($servername,$username,$password,$dbname);
if($conn->connect_error){
	die("Connection failed:".$conn->connect_error);
}      
        $conn = new mysqli($servername, $username, $password, $dbname);
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO ESPData (SensorData, LocationData, value1, value2, value3)
        VALUES ('" . $SENSORDATA . "', '" . $LOCATIONDATA . "', '" . $value1 . "', '" . $value2 . "', '" . $value3 . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key";
    }
 
}
else {
    echo "No data posted HTTP POST.";
}
 
function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}