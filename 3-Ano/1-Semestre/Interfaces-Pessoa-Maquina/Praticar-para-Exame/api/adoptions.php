<?php
  
include 'db.php';

if($_SERVER['REQUEST_METHOD'] == 'POST') {
	
	// ligação à base de dados
	$db = dbconnect($hostname,$db_name,$db_user,$db_passwd);
	if($db) {	

		$json=file_get_contents('php://input');

		$data = json_decode($json, true);

		// criar query numa string
		$query  = "INSERT INTO adoptions SET petlover_id='" . $data['petlover_id'] . "',pet_id='" . $data['pet_id']  . "',created_at=NOW()";

		// executar a query
		if(!($result = @ mysqli_query($db, $query)))
			showerror($db);
			
		$petlover_id=$data['petlover_id'];
		// get last order id
			$query = "select a.id, a.created_at, p.name as pet_name, p.image as pet_image from adoptions as a inner join (pets as p, petlovers as c) on (a.pet_id=p.id and a.petlover_id=c.id ) where a.petlover_id='$petlover_id' order by a.id desc limit 1";
			if(!($result = @ mysqli_query($db, $query)))
				showerror($db);
			   
			$last_order = mysqli_fetch_assoc($result);

		// update pet status 
		$query = "UPDATE pets SET status='1' WHERE id='" . $data['pet_id'] . "'";
		if(!($result = @ mysqli_query($db, $query)))
			showerror($db);

		// fechar a ligação à base de dados
		mysqli_close($db);

	} // end if db		
		
	// allow cross-origin requests (CORS)
	header('Access-Control-Allow-Origin: *');
	header("Access-Control-Allow-Methods: GET, POST, OPTIONS, PUT, DELETE");
	header("Access-Control-Allow-Headers: Authorization, Origin, User-Token, X-Requested-With, Content-Type");
	// convert to JSON
	$json=json_encode($last_order);
	echo $json;
		
	
}
	
    if($_SERVER['REQUEST_METHOD'] == 'GET') {
		
		// ligação à base de dados
		$db = dbconnect($hostname,$db_name,$db_user,$db_passwd);
		if($db) {	
			$petlover_id = $_GET['petlover_id'];
		
			$query = "select a.id, a.created_at,  p.name as pet_name, p.image as pet_image, p.description as pet_description from adoptions as a inner join (pets as p, petlovers as c) on (a.pet_id=p.id and a.petlover_id=c.id ) where a.petlover_id='$petlover_id' order by a.created_at desc";
			
			if(!($result = @ mysqli_query($db, $query)))
				showerror($db);
			// vai buscar o resultado da query

			$nrows  = mysqli_num_rows($result);
			$adoptions = [];
			for($i=0; $i<$nrows; $i++)
				$adoptions[$i] = mysqli_fetch_assoc($result);

			// fechar a ligaçãbase de dados
			mysqli_close($db);

		} // end if db 	
		
		// allow cross-origin requests (CORS)
		header('Access-Control-Allow-Origin: *');
		header("Access-Control-Allow-Methods: GET, POST, OPTIONS, PUT, DELETE");
		header("Access-Control-Allow-Headers: Authorization, Origin, User-Token, X-Requested-With, Content-Type");
		// convert to JSON
		$adoptionsJSON = json_encode($adoptions);
		echo $adoptionsJSON;
		
    }

	// allow cross-origin requests (CORS)
	if($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
		header('Access-Control-Allow-Origin: *');
		header("Access-Control-Allow-Methods: GET, POST, OPTIONS, PUT, DELETE");
		header("Access-Control-Allow-Headers: Authorization, Origin, User-Token, X-Requested-With, Content-Type");	
	}	    



?>


