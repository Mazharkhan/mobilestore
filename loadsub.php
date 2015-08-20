<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

require 'class.dbhelper.inc';
// Object Created of Class clsdbhelper
$objDB = new clsdbhelper();

//Check Which Dropdown is Selected
$passkey = explode('=', $_SERVER['QUERY_STRING']) ;

if ($passkey[0] === 'brandID'){
    // Variable to get brand ID
$brandID = $_GET['brandID'];
// Call Function to Get Data to fill mobile brands
$resultmodel = $objDB->fillmobilemodel($brandID);

 while ($row = $resultmodel->fetch(PDO::FETCH_ASSOC)) {
                            echo "<option value='" . $row['modelID'] . "'>" . $row['modelname'] . "</option>";
                        }
}elseif ($passkey[0] === 'stateID') {
    // Variable to get brand ID
    $stateID = $_GET['stateID'];

    $resultcity =  $objDB->fillcity($stateID);
            
   while ($row = $resultcity->fetch(PDO::FETCH_ASSOC)) {
                            echo "<option value='" . $row['cityid'] . "'>" . $row['cityname'] . "</option>";
                        }
}

                        

