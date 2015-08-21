<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of class
 *
 * @author Designer
 */
class clsdbhelper extends conndatabase {
    
    
    // Function to Add User
    public function adduser($pusername,$pemailaddr,$pmobilenum){
        
         if ($this->_connection === null){
            $this->reconnect();
        }
        
        $conn = $this->_connection;
        $result=$conn->prepare('call sp_adduser(:p_username, :p_useremail, :p_userphone)');
        $result->bindParam(':p_username', $pusername, PDO::PARAM_STR);
        $result->bindParam(':p_useremail', $pemailaddr, PDO::PARAM_STR);
        $result->bindParam(':p_userphone', $pmobilenum, PDO::PARAM_STR);
        $result->execute();
        
        $output = $conn->query('SELECT LAST_INSERT_ID();');
        $returnID = $output->fetchColumn(0);
        
        
        return $returnID;
    }


    // Function to Add new post
    public function addnewpost($pTitle,$pDesc,$pBrandID,$pModelID,$piOS,$pNumSim,$pStateID,$pCityID,$pLocID,$pUserID,$pPostdate,$pUsed,$pmobprice){
        if ($this->_connection === null){
            $this->reconnect();
        }
        
        $conn = $this->_connection;
        $result = $conn->prepare('call sp_addnewpost(:p_vtitle, :p_vdesc, :p_ibrandID,:p_imodelID, :p_iosID, :p_inumSIM, :p_istateID, :p_icityID, :p_ilocalatyID, :p_iuserid, :p_dposteddate, :p_used, :p_mobprice" )');
        $result->bindParam(":p_vtitle",$pTitle,  PDO::PARAM_STR);
        $result->bindParam(":p_vdesc",$pDesc,  PDO::PARAM_STR);
        $result->bindParam(":p_ibrandID",$pBrandID,  PDO::PARAM_INT);
        $result->bindParam(":p_imodelID",$pModelID,  PDO::PARAM_INT);
        $result->bindParam(":p_iosID",$piOS,  PDO::PARAM_INT);
        $result->bindParam(":p_inumSIM",$pNumSim,  PDO::PARAM_INT);
        $result->bindParam(":p_istateID",$pStateID,  PDO::PARAM_INT);
        $result->bindParam(":p_icityID",$pCityID,  PDO::PARAM_INT);
        $result->bindParam(":p_ilocalatyID",$pLocID,  PDO::PARAM_INT);
        $result->bindParam(":p_iuserid",$pUserID,  PDO::PARAM_INT);
        $result->bindParam(":p_dposteddate",$pPostdate, PDO::PARAM_STR);
        $result->bindParam(":p_used",$pUsed,  PDO::PARAM_INT);
        $result->bindParam(":p_mobprice", $pmobprice,  PDO::PARAM_STR);
        $result->execute();
        
        $output = $conn->query('SELECT LAST_INSERT_ID()');
        $returnID = $output->fetchColumn(0);
        
        return $returnID;
    }

    // Fuction to fill State dropdown
    public function fillstate(){
        if ($this->_connection === null){
            $this->reconnect();
        }
        
        $conn = $this->_connection;
        $result = $conn->prepare('call sp_stateget()');
        $result->execute();
        return $result;
        
    }
    
    //Fucntion to fill City dropdown on StateID
    public function fillcity($stateID){
        
        if ($this->_connection === null){
            $this->reconnect();
        }
        
        $conn = $this->_connection;
        $result = $conn->prepare('call sp_cityget(?)');
        $result->bindParam(1,$stateID,  PDO::PARAM_INT);
        $result->execute();
        return $result;
    }
    
    // Function to fill Brand name of Mobile phone
    public function fillmobilebrand(){
        
        if ($this->_connection === null){
            $this->reconnect();
        }
        
        $conn = $this->_connection;
        $resultbrand = $conn->prepare('call sp_mobilebrandget()');
        $resultbrand->execute();
        return $resultbrand;
    }
    
    // Function to fill Mobile model based on Brand
    public function fillmobilemodel($brandID){
        
        if ($this->_connection === null){
            $this->reconnect();
        }
        
        $conn = $this->_connection;
        $result = $conn->prepare('call sp_mobilemodelget(?)');
        $result->bindParam(1,$brandID,  PDO::PARAM_INT);
        $result->execute();
        return $result;
    }
    
}

class conndatabase {
    private $_username = 'sa';
    private $_password = 'wwww123';
    
    
    public $_connection;
    private  static $_instance;
    
    public static function getInstance(){
        if (!self::$_instance){
            self::$_instance  = new self();
        }
        return self::$_instance;
    }
    
    
    public function  __construct(){
        // PDO Connection Type 
        $this-> _connection = new PDO('mysql:dbname=mobile15;host=127.0.0.1;', $this->_username, $this->_password);
    }
    
    public function reconnect() {
        $this->_connection = new PDO('mysql:dbname=mobile15;host=127.0.0.1;', $this->_username, $this->_password);
    }
}
