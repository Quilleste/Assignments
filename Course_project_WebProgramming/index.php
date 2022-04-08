<?php
//Kulyk Y. O.
//04.06.2021
//v 1.0
//04.06.2021
?>
<html>
<head>
	<meta charset="utf-8" ></meta>
	<link href="style.css" rel="stylesheet">
	<link rel="icon" type="image/ico" href="media/ico.ico" />
	<title>KP</title>
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/2.0.3/jquery.min.js"></script>
</head>
<body>


<!-- Заготовленный блок -->
<a name="15"></a>
	<p><h1 class="lab" style="font-size:40;width:500;" align="center">Курсовой проект.</h1></p><br/>
	 
	<h1 align="center" style="color:#ececeb;margin-left:2%;">Задание.</h1>
<!-- Завдання! -->
<pre class="lab"  >
Получить доступ к базе данных, выбрать данные из определенного промежутка, построить выбраные пользователем графики.
</pre>
<h1 align="center" style="color:#ececeb;margin-left:2%;">Выполнение задания.</h1>
<!-- Выполнение задания. -->
<?php
$hostname = "localhost";
$username = "root";
$password = "shana1";
$msg = "Trying to connect...";

$bd = mysql_connect($hostname, $username, $password);
if (!$bd)  {
	$msg .= "<br> Can't connect! ";
} else {
	$msg .= "<br> Connected successfully! <br>Looking for the values. <br>";
	if(mysql_select_db("values")) {
		mysql_query("set character_set_client='utf8_bin'");
		mysql_query("set character_set_results='utf8_bin'");
		mysql_query("set collation_connection='utf8_bin'");
		$sql = "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'vals'";
		if(($res = mysql_query($sql)) != false) { 
			list($count) =  mysql_fetch_row($res);
			$msg .= "Number of numeric values: " . ($count - 2) . "<br>";
			$sql = "SELECT * FROM vals";
			if(($res = mysql_query($sql)) != false) {
			
				for($i = 0; $i < mysql_num_rows($res); $i++) {
					for($k = 0; $k < $count; $k++) {
						$msg .= mysql_result ($res , $i, $k)  . " | ";
					}
					$msg .= "<br>"; 
				}
			} else {
			$msg .= "Can't make SQL-query! <br>";
			}
		
		} else $msg .= "Can't make SQL-query for column count! <br>"; 
		
		$msg .= "<br>";
		
	} else {
		$msg .= "Can't open the database.";
	}
}
mysql_close($bd);
?>

<div class="lab" id="divBD"> <?php echo $msg;  ?></div> 
<br>

<div class="lab" id="forma">
<form method="post">
<p>From: </p>
<input type="date" id="start_date" name="trip-start"
       value="2021-05-01"
       min="2021-05-01" max="2021-05-20">
<p>To: </p>
<input type="date" id="end_date" name="trip-end"
       value="2021-05-01"
       min="2021-05-01" max="2021-05-20">
<p>Choose the graphs to show: </p>
<?php
	$html_msg;
	for($i = 0; $i < ($count-2); $i++) {
		$html_msg .= '<input type="checkbox" name="vals[]" value="val' . ($i+1) . '">';
		$html_msg .= '<label for="val' . ($i+1) . '"> Graph for val' . ($i+1) . '</label><br>';
	}
	$html_msg .= "</p>";
	echo $html_msg;
?>
<p><input value="Generate" id="submit_btn" type="submit"/></p>
</form> 
</div>
<br>
<div class="lab" id="divImg"> 
<?php
function display_graph()
{
$allow = false;
require_once ('jpgraph/src/jpgraph.php');
require_once ('jpgraph/src/jpgraph_line.php');


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
	$arr_needles = array();
	$ExArray = array(array());

	if((date('Ymd', strtotime($_POST['trip-start'])) - date('Ymd', strtotime($_POST['trip-end']))) > 0) {
		$msg .= "<br> End date can't be smaller than begining date!<br>";
	} else {
	$msg .= "<br> Connected successfully! <br>Looking for the fitting values. <br>";
	if(mysql_select_db("values")) {
		mysql_query("set character_set_client='utf8_bin'");
		mysql_query("set character_set_results='utf8_bin'");
		mysql_query("set collation_connection='utf8_bin'");
		$sql = "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'vals'";
		if(($res = mysql_query($sql)) != false) { 
			//определение, какие столбцы нужно вывести
			list($count) =  mysql_fetch_row($res);
			for($i = 0; $i < ($count-2); $i++) {
				$needle = "val" . ($i+1);
				if(in_array($needle, $_POST["vals"])) {
					$arr_needles[$i] = true;
				} else $arr_needles[$i] = false;
			}
			$sql = "SELECT * FROM vals WHERE date_val BETWEEN '" . $date_beg . "' AND '" . $date_end . "'";
			if(($res = mysql_query($sql)) != false) {
			
				for($i = 2; $i < $count; $i++) {
					for($k = 0; $k < mysql_num_rows($res); $k++) {
						$ExArray[($i-2)][$k] = mysql_result ($res , $k, $i); 
					}
					$msg .= "<br>"; 
				}
				$msg .= "Creating a graph. <br>";	
			$allow = true;
			} else {
			$msg .= "Can't make SQL-query! <br>";
			}
		
		} else $msg .= "Can't make SQL-query for column count! <br>"; 
		
		$msg .= "<br>";
		
		} else {
		$msg .= "Can't open the database.";
	}
	}
}
//echo $msg;
if($allow) {
	
$colors = array("teal", "red", "azure3", "blueviolet", "chartreuse4", "cornsilk", "darkolivegreen3");

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


for($i = 0; $i < count($arr_needles); $i++) {
	if($arr_needles[$i]) {
		$p2 = new LinePlot($ExArray[$i]);
		$p2->SetColor($colors[$i]);
		$p2->SetLegend(("val" . ($i+1)));
		$graph->Add($p2);
	}
	
}

$src = 'myimage.png';

if (@getimagesize($src)) {
	unlink($src);
	$graph->Stroke('myimage.png');
} else {
	$graph->Stroke('myimage.png');
}
} 
}
if($_SERVER['REQUEST_METHOD']=='POST') {
       display_graph();
}

?>
<img src="myimage.png"></div> 
<br>

<!-- Заготовленный блок -->
</body>
</html>
