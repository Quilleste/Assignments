<html>
<head>
	<meta charset="utf-8" ></meta>
	<link href="style.css" rel="stylesheet">
	<link rel="icon" type="image/ico" href="media/ico.ico" />
	<title>Lab15</title>
	<!-- <script src="script.js" type="text/javascript"></script> -->
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/2.0.3/jquery.min.js"></script>
	<script src="ajax.js"></script>
</head>
<body>


<!-- Заготовленный блок -->
<a name="15"></a>
	<p><h1 class="lab" style="font-size:40;width:500;" align="center">Лабораторна робота №15.</h1></p><br/>
	 
	<h1 align="center" style="color:#ececeb;margin-left:2%;">Завдання (варіант 8).</h1>
<!-- Завдання! -->
<pre class="lab"  >
Створити XML файл на тему "Сантехніка", обов'язкові поля: "Назва товару", "Матеріал", "Розміри", "Ціна".

Студент: Кулик Я. О.
Група: КІТ-М120д
</pre>
<h1 align="center" style="color:#ececeb;margin-left:2%;">Виконанння завдання.</h1>
<!-- Выполнение задания. -->
<div class="lab" >
<?php
$xml = "SanitaryFixture.xml";
$res = simplexml_load_file($xml);
foreach($res->Product as $val) {
	echo "Product: " . $val->ProductName . "<br>";
	echo "Material: " . $val->Material . "<br>";
	echo "Price: " . $val->Price . "<br>";
	echo "Size info: <br>";
	echo "-Height: " . $val->Size->Height . "<br>";
	echo "-Width: " . $val->Size->Width . "<br>";
	echo "-Length: " . $val->Size->Length . "<br>";
	echo "------------------------------------------------------------------- <br>";
}

$child = $res->addChild('Product');
$child->addChild('ProductName', "Testproduct");
$child->addChild('Material', "Testmaterial");
$child->addChild('Price', "Testprice");

$childSize = $child->addChild('Size');
$childSize->addChild('Height', 'testHeight');
$childSize->addChild('Width', 'testWidth');
$childSize->addChild('Length', 'testLength');

echo "XML после использования addChild() <br>";
echo "------------------------------------------------------------------- <br>";
foreach($res->Product as $val) {
	echo "Product: " . $val->ProductName . "<br>";
	echo "Material: " . $val->Material . "<br>";
	echo "Price: " . $val->Price . "<br>";
	echo "Size info: <br>";
	echo "-Height: " . $val->Size->Height . "<br>";
	echo "-Width: " . $val->Size->Width . "<br>";
	echo "-Length: " . $val->Size->Length . "<br>";
	echo "------------------------------------------------------------------- <br>";
}
echo "Поиск дочерних элементов (по наименованию): <br>";
echo "------------------------------------------------------------------- <br>";
foreach ($res->children() as $prodChild) {
    echo ' В наличии есть ' . $prodChild->ProductName . ". <br>";
}
echo "------------------------------------------------------------------- <br>";
?>
</div>

<!-- Заготовленный блок -->
</body>
</html>