<?php
//Kulyk Y. O.
//04.06.2021
//v 1.0
//04.06.2021
header("Content-Type: image/png");
$allow = false;
require_once ('jpgraph/src/jpgraph.php');
require_once ('jpgraph/src/jpgraph_line.php');

$x_val = array();
$y1 = array();
$y2 = array();
$y3 = array();

$hostname = "localhost";
$username = "root";
$password = "shana1";
$msg = "Trying to connect...";

$bd = mysql_connect($hostname, $username, $password);
if (!$bd)  {
	$msg .= "<br> Can't connect! ";
} else {
	$date_beg = date('Y-m-d', strtotime($_POST['trip-start']));
	$date_end = date('Y-m-d', strtotime($_POST['trip-end']));
	$v1 = false;
	$v2 = false;
	$v3 = false;
	if(isset($_POST['vals1'])) {
		$v1 = true;
	}
	if(isset($_POST['vals2'])) {
		$v2 = true;
	}
	if(isset($_POST['vals3'])) {
		$v3 = true;
	}

	if((date('Ymd', strtotime($_POST['trip-start'])) - date('Ymd', strtotime($_POST['trip-end']))) > 0) {
		$msg .= "<br> End date can't be smaller than begining date!<br>";
	} else {
	$msg .= "<br> Connected successfully! <br>Looking for the fitting values. <br>";
	if(mysql_select_db("values")) {
		mysql_query("set character_set_client='utf8_bin'");
		mysql_query("set character_set_results='utf8_bin'");
		mysql_query("set collation_connection='utf8_bin'");
		$sql = "SELECT id,val1,val2,val3 FROM vals WHERE date_val BETWEEN '" . $date_beg . "' AND '" . $date_end . "'";
		if(($res = mysql_query($sql)) != false) {
			
				for($i = 0; $i < mysql_num_rows($res); $i++) {
					list($id, $val1, $val2, $val3) =  mysql_fetch_row($res);
					$x_val[] = $id;
					$y1[] = $val1;
					$y2[] = $val2;
					$y3[] = $val3;
				}
			$msg .= "Creating a graph. <br>";	
			$allow = true;
		} else {
			$msg .= "Can't make SQL-query! <br>";
		}
		
		$msg .= "<br>";
				

		
	} else {
		$msg .= "Can't open the database.";
	}
	}
}
//echo $msg;
if($allow) {

$graph = new Graph(550,350);
$graph->clearTheme();
$graph->SetMargin(40,150,40,30);
$graph->SetMarginColor('white');

$graph->legend->SetAbsPos(10,10,'right','top');

$graph->SetScale('intlin');
$graph->title->Set('Graph');
$graph->title->SetFont(FF_ARIAL,FS_NORMAL,14);
$graph->yaxis->title->Set('(Values of val)');
$datas = "From " . $date_beg . " to " . $date_end;
$graph->xaxis->title->Set($datas);

//$graph->SetYScale(0,'lin');
//$graph->SetYScale(1,'lin');

if($v1) {
$p1 = new LinePlot($y1);
$p1->SetLegend("val1");
$graph->Add($p1);
}
if($v2) {
$p2 = new LinePlot($y2);
$p2->SetColor('teal');
$p2->SetLegend("val2");
$graph->Add($p2);
}
if($v3) {
$p3 = new LinePlot($y3);
$p3->SetColor('red');
$p3->SetLegend("val3");
$graph->Add($p3);
}



$graph->Stroke();

}
?>