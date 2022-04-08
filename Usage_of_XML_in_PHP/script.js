function hideLoader(){
	document.getElementById("loading").style.display="none";
	console.log("Page loaded");
}
function authorSet(){
	document.getElementById("author").innerHTML="<div align=left style=padding:5;padding-left:5; ><p><h3 style=color:#839496; >Лабораторна робота.</h3></p><p style=color:#839496; >Курс: Веб програмування.</p><p style=color:#839496; >Студент: Недашківський Денис</p><p style=color:#839496; >Группа: КІТ-16Б</p><p style=color:#839496; >Номер по списку: 17</p></div>";
}
function findLeapYear(year){
if((year % 4) == 0){return year;}
var result;
while((year % 4) != 0){year--;result=year;}
if(result>=0){return result;}else{return 0;}
}
function month(m){
 var mass = [ 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4, ];// с января по декабрь
 return mass[m-1];
}
function nOfWeek(d,m,y){
var syear =findLeapYear(y);
if(syear == 0){return 0;}
return ((d+month(m)+syear)%7);
}
function addResult(str,idOfTag){
	var x = document.getElementById(idOfTag)
	x.className ="lab";
	x.style.color = "green";
	x.style.backgroundColor = "black";
	x.innerHTML +=str;
}
function viewArr3(z,arr){
	var result="<div class=lab style=background-color:#000000;width:100; >";
	console.log(arr.valueOf());
		var key1Arr3 = new Array(0);
		for (var prop in arr) {
			key1Arr3.push(prop)
		}
			for(var i=0;i<=key1Arr3.length-1;i++){
				result+="<p class=lab style=background-color:#111111;>"+key1Arr3[i]+": </p>";			

		var key2Arr3 = new Array(0);
		for (var prop in arr[key1Arr3[i]]) {
			key2Arr3.push(prop)
		}			
				for(var j=0;j<=key2Arr3.length-1;j++){
					result+="<p   class=lab style=background-color:#1a1a1a;margin-left:20; >"+key2Arr3[j]+": </p>";
						for(var k=0;k<=arr[key1Arr3[i]][key2Arr3[j]].length-1;k++){
							result+="<p   class=lab style=background-color:#333333;margin-left:40; >"+arr[key1Arr3[i]][key2Arr3[j]][k]+"</p>";
					}
				}	
			}
	z.innerHTML = result+="</div>";
}
function objSize(obj){
	var counter = 0;
	for (var key in obj) {
	  counter++;
	}
	return counter;
}
function getName(x){
	try{var temp = prompt(x);
	if(temp != null){
		if(temp.charAt(0) != " "){
			if(isNaN(temp)){
				return temp;
			}else{getName(x);}
		}else{getName(x);}
	}else{getName(x);}
	}catch(e){
		allert(e.message);
	}
}
function getGroup(x){
	try{var temp = prompt(x);
	if(temp != null){
		if(temp.charAt(0) != " "){
			return temp;
		}else{getGroup(x);}
	}else{getGroup(x);}
	}catch(e){
		allert(e.message);
	}
}
function test(task,correctAnswer,currentScore){
	if(confirm(task) == correctAnswer){
		currentScore++;
	}
	return currentScore;
}
function charRand(){
	mass = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',0,1,2,3,4,5,6,7,8,9]
	return mass[Math.floor(Math.random() * 36)]
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
function lab9() {
  //console.log("test");
  alert( 'Тест на тему "Задание размера символов"' );
  if(confirm( 'Начать тест?' )){
  var score = 0;
  var sName = getName('Введите ваше имя'); 
  var group = getGroup('Введите вашу группу');
  
  score = test("Тег <font> может содержать в себе атрибут size?",true,score);
  score = test("Данная строка изменит размер внутри тега <p>? \n <p style=font-stretch:12px >text</p>",false,score);
  score = test("Тег <big> нужно закрывать?",true,score);
  score = test("Данная строка изменит размер внутри тега <p>? \n <p style=font-size:12px >text</p>",true,score);
  
  alert("Фамилия: "+sName+"\nГруппа: "+group+"\nРезультат: "+score);
  }else{alert( 'Тест отклонён' );}
  
}
function lab10(){

var arr = [1,2,3.1,4.1,5.1,"строкa","строкa","строкa","строкa","строкa"];
var x = document.getElementById("lab10_result");
	var nums	= 0;
	var result	= 0;
	
	for(var a = 0;a <= arr.length-1;a++){
		if(!isNaN(arr[a])){
			result += arr[a];
			nums++;
			//console.log(result+" "+arr[a]+" "+ nums);
		}
	}
	result = result / nums;
	
var arr2 = new Map([
  ['b', 'value1'],
  ['c', 'value2'],
  ['a', 'value3'],
  ['d', 'value4'],
  ['g', 'value5']
]);  
var keyArray = Array.from(arr2.keys());
keyArray.sort();
var key = keyArray[0];
var arr3 = {

	"a": {
		"x": [ "2,5" ],
		"y": [ "1,25" ]
	},
	"b": {
		"x": [ "5,0" ],
		"y": [ "2,5" ]
	}

};
var meggaArr=0;
x.innerHTML = "<h3 class=lab style=background-color:black;color:green;>&gt; Array: "+arr.join(" , " )+"<br/>&gt; Result: "+result+"<br/>&gt; Result2: "+key+"<br/>&gt; Result3: <br/><br/><code id=arr3 ></code><br/>&gt; browser: "+navigator.userAgent+" </h3>";
var z = document.getElementById("arr3");
viewArr3(z,arr3)
	
}
function lab11(){
var style = document.getElementById("lab11_style");
var div = document.getElementById("lab11_block");
style.innerHTML	= ".lab11_class{background-color:white;}";
div.innerHTML		= "<h1>Встроенная модель</h1>";
div.style="margin-top:2%;text-shadow:1px 1px 2px black, 0 0 1em red;";
}
function lab112(){
var style = document.getElementById("lab11_style");
var div = document.getElementById("lab11_block");
style.innerHTML	= ".lab11_class{}";
div.style.backgroundColor = "none";
div.innerHTML= "<h1>Традиционная модель</h1>";
div.style="margin-top:2%;text-shadow:1px 1px 2px black, 0 0 1em none;";	  
}
function lab113(){
var style = document.getElementById('lab11_style');
var div = document.getElementById('lab11_block');
style.innerHTML	= ".lab11_class{}";
div.style.backgroundColor = "red";
div.innerHTML= "<h1>Усовершенствованная модель</h1>";
}
function lab14_1(){
var timeLine=10;
var d=13;
var y = 2018;
var counter = 0;
	for(var i = y-timeLine+1;i != y+1;i++){
		for(var j = 1;j <= 12;j++){
			if(nOfWeek(d,j,i) == 5){
				counter++;
			}
		}
	}	
	 addResult("&gt "+counter+" раз за последние 10 лет</br>","lab14_result");
} 
function lab14_2(x){
	addResult("&gt x: "+x+" -&gt "+(Math.log((x*2)+Math.sqrt(x))+Math.LN2)+"</br>","lab14_result");
}
function lab15(){
var form = document.getElementById('lab15').elements;
var myWindow = window.open("", "MsgWindow", "width=100,height=100");
myWindow.document.write("<body style=background-color:#36393f; ><img width=50 src=media/j"+form['изделия'].value+".png />");
document.cookie= form['имя'].value+"="+form['пол'].value+":"+form['образование'].value+":"+form['изделия'].value;
//document.cookie="foo=bar; path=/; expires=Mon, 01-Jan-2125 00:00:00 GMT"
}
function lab15_1(){
	var cookieString = document.cookie;
	if(isNaN(cookieString)){
	var counter = 0;
	var counterM = 0;
	for(var i = 0;i<=cookieString.length-1;i++){
		if(cookieString.charAt(i) == "="){
			counter++;
			if(cookieString.charAt(i+1) == "м"){
				counterM++;
			}
		}
	}
	addResult("result: "+(Math.floor((counterM/counter)*100))+"%</br>","lab15_result");
	}else{
		addResult("нет куки для обработки</br>","lab15_result");
	}
}
function lab16(){
	var form = document.getElementById('lab16').elements;
	var reg1 = /^ЗК:[0-9]{5} [0-9]{10}$/;
	var reg2 = /^[А-Я]{1}[а-я]{2,50} [А-Я]{1}\.[А-Я]{1}\.$/;
	var reg3 =/^груп\. [А-Я]{3}\-[0-9]{1}[0-9а-я]{1}([а-я]{0,1})? с_т .*$/;
	
	var result1 = form['Данные1'].value.match(reg3);
	var result2 = reg2.exec(form['Данные2'].value);
	var result3 = reg1.exec(form['Данные3'].value);
	if(result1.length >0){result1 = true;}else{result1 = false;}
	if(result2.length >0){result2 = true;}else{result2 = false;}
	if(result3.length >0){result3 = true;}else{result3 = false;}
	//груп. КИТ-16б с_т Факультеты выфв
	//Аззи А.В.
	//ЗК:32564 5598548985
	addResult("Данные1: "+result1+" Данные2: "+result2+" Данные3: "+result3,"lab16_result")
}
function lab18(x){
	var result = document.getElementById('lab18_result');
	var reg = /^.*\.jpg$/;
	var mass = [];
	for(var i=0;i<= x.length-1 ;i++){
		var str = x[i].name;
		if(reg.exec(str)!= null){mass.push(i);}		
	}
	
	for(var i=0;i<= mass.length-1 ;i++){		
		result.innerHTML +="<img width=50 height=50 src="+window.URL.createObjectURL(x[mass[i]])+"  ></img>"
	}
}
function lab18_2(){
	var x = document.getElementsByTagName("img");
	for(var i =0;i<= x.length-1;i++){
		addResult((i+1)+"| "+x[i].attributes.src.value+"</br>","lab18_result2");
	}
}
function lab19(){
	var apiKey = "f65de391-a961-4b8c-a6b7-0219884d2122";
	var invokeURL = "https://api.random.org/json-rpc/2/invoke";
	var method = "POST";
	var nums=42;
	var min=17;
	var max=60;
	var col=5;
	//lab19_result - id to result
	var JSONobj = 
	{"jsonrpc": "2.0","method": "generateIntegers","params": {"apiKey": apiKey,"n": nums,"min": min,"max": max,"replacement": true},"id": 1337};
	var jsonString = JSON.stringify(JSONobj)
	var xhr=new XMLHttpRequest(); 
	xhr.open(method, invokeURL);
	xhr.setRequestHeader('Content-Type', 'application/json');
	try{xhr.send(jsonString);
	}catch(e){addResult("xhr: "+e+"</br>","lab19_result");}
	xhr.onerror=function(e) {
	addResult("xhr: "+Error+"</br>","lab19_result");
	} 
	xhr.onload=function() {
		var resp=this.response;//
		var res=JSON.parse(resp);
		addResult("Result_1: </br>","lab19_result");
		var mass1=[];
		for(var i = 0;i<= res.result.random.data.length-1;i++){
			if (res.result.random.data[i] % 2 == 0){mass1.push(res.result.random.data[i]);}
		}
		for(var i = 0;i<= mass1.length-1;i++){
			var br;
			if((i+1) % 5 == 0){br = "</br>";}else{br= " ";}
			addResult(mass1[i]+br,"lab19_result");
		}
	}		
}
function lab19_2(){
	var mass =[];
	var mass2 =[];
	var brCount = 22;
	var stringCount = 10;
	addResult("</br>lab19_2.mass: </br></br>","lab19_result");
	for(var i = 0;i<= stringCount-1;i++){
		var stringMass =[];
		for(var j = 0;j<= brCount-1;j++){
			stringMass.push(charRand());
		}
		mass[i]=(stringMass.toString()).replace(/,/g, '');
		addResult(mass[i]+"</br>","lab19_result");
	}
	
	addResult("</br>lab19_2.mass2: </br></br>","lab19_result");
	for(var i = 0;i<= mass.length-1;i++){
		var tempString="";
		for(var j = 0;j<= mass[i].length-1;j++){
			if(!isNaN(mass[i].charAt(j))){
				tempString+=mass[i].charAt(j);
			}
		}
		mass2.push(tempString);
		addResult(mass2[i]+"</br>","lab19_result");
	}
	

}
function lab19_3(x){
var result = document.getElementById('lab19_result');
	var reg = /^.*\.png$/;
	var reg2 = /^.*\.mp4$/;
	var massImg = [];
	var massVideo = [];
	for(var i=0;i<= x.length-1 ;i++){
		var str = x[i].name;
		if(reg.exec(str)!= null){massImg.push(i);}		
		if(reg2.exec(str)!= null){massVideo.push(i);}		
	}
	for(var i=0;i<= massImg.length-1 ;i++){		
		result.innerHTML +="<img width=200 height=200 src="+window.URL.createObjectURL(x[massImg[i]])+"  ></img>"
	}	
	for(var i=0;i<= massVideo.length-1 ;i++){		
		result.innerHTML +="<video controls width=200 height=200 src="+window.URL.createObjectURL(x[massVideo[i]])+"  ></video>"
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
window.onload = function() {
    setTimeout("hideLoader()", 5000);
	authorSet();
	//setTimeout("lab18_2()", 5500);
};
document.addEventListener('DOMContentLoaded', function () {
document.addEventListener ("keydown", function (zEvent) {
    if (zEvent.altKey &&  zEvent.code === "KeyA") {
        lab15_1();
    }
} );
document.getElementById('l112').ondblclick=lab112;//element.addEventListener(event, function, useCapture),
document.getElementById('l113').addEventListener("dblclick", lab113, false);});