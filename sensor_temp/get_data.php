<?php

include 'DatabaseConfig.php' ;

$con = mysqli_connect($HostName,$HostUser,$HostPass,$DatabaseName);


$temp = $_POST['temp'];

$Sql_Query = "insert into weather (temp) values ('$temp')";

if(mysqli_query($con,$Sql_Query)){

    echo 'Data Submit Successfully';

}
else{

    echo 'Try Again';

}
mysqli_close($con);
?>