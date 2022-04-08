function addResult(str,idOfTag){
	var x = document.getElementById(idOfTag)
	x.className ="lab";
	x.style.color = "black";
	x.innerHTML +=str;
}

function charRand(){
	mass = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',0,1,2,3,4,5,6,7,8,9]
	return mass[Math.floor(Math.random() * 36)]
}

function lab19(){
	var apiKey = "f65de391-a961-4b8c-a6b7-0219884d2122";
	var invokeURL = "https://api.random.org/json-rpc/2/invoke";
	var method = "POST";
	var nums = 32;
	var min = 0;
	var max = 59;
	var col = 3;
	//lab19_result - id to result
	var JSONobj = 
	{"jsonrpc": "2.0","method": "generateIntegers","params": {"apiKey": apiKey,"n": nums,"min": min,"max": max,"replacement": true},"id": 1337};
	var jsonString = JSON.stringify(JSONobj)
	var xhr=new XMLHttpRequest(); 
	xhr.open(method, invokeURL);
	xhr.setRequestHeader('Content-Type', 'application/json');
	try{xhr.send(jsonString);
	}catch(e){addResult("xhr: "+e+"</br>","lab19_result");}
	xhr.onerror = function(e) {
	addResult("xhr: "+Error+"</br>","lab19_result");
	} 
	xhr.onload=function() {
		var resp=this.response;//
		var res=JSON.parse(resp);
		addResult("Rand array: </br>","lab19_result");
		
		for(var i = 0;i<= res.result.random.data.length-1;i++){
			var br;
			if((i+1) % 3 == 0){br = "</br>";}else{br= " ";}
			addResult(res.result.random.data[i]+br,"lab19_result");
		}
		addResult("</br>", "lab19_result");
		addResult("Sum: ","lab19_result");
		var mass1 = 0;
		for(var i = 0;i<= res.result.random.data.length-1;i++){
			mass1 += res.result.random.data[i];
		}
		addResult(mass1 + "</br>" + "</br>" + "</br>","lab19_result");
	}		
}
function lab19_2(){
	var mass =[];
	var mass2 =[];
	var brCount = 48;
	var stringCount = 5;
	addResult("Array: </br></br>","lab19_result");
	for(var i = 0;i<= stringCount-1;i++){
		var stringMass =[];
		for(var j = 0;j<= brCount-1;j++){
			stringMass.push(charRand());
		}
		mass[i]=(stringMass.toString()).replace(/,/g, '');
		addResult(mass[i]+"</br>","lab19_result");
	}
	
	addResult("</br>Sum in each row: </br></br>","lab19_result");
	for(var i = 0;i<= mass.length-1;i++){
		var tempString = 0;
		for(var j = 0;j<= mass[i].length-1;j++){
			if(!isNaN(mass[i].charAt(j))){
				tempString += parseInt(mass[i].charAt(j));
			}
		}
		mass2.push(tempString);
		addResult(mass2[i]+"</br>","lab19_result");
	}
	addResult("</br>","lab19_result");
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
		result.innerHTML +="<img width=100 height=100 src="+window.URL.createObjectURL(x[massImg[i]])+"  ></img>"
	}	
	for(var i=0;i<= massVideo.length-1 ;i++){		
		result.innerHTML +="<video controls width=100 height=100 src="+window.URL.createObjectURL(x[massVideo[i]])+"  ></video>"
	}
}

function lab15(){
var form = document.getElementById('lab15').elements;
var myWindow = window.open("", "NewWindow", "width=500,height=500");
myWindow.document.write("<body><img width=450 src="+form['изделия'].value+".jpg />");
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
	addResult("Male visitors: "+(Math.floor((counterM/counter)*100))+"%</br>","lab15_result");
	}else{
		addResult("No set cookies!</br>","lab15_result");
	}
}

window.onload = function() {
    setTimeout("hideLoader()", 10000);
	//setTimeout("lab18_2()", 5500);
};
document.addEventListener ("keydown", function (zEvent) {
    if (zEvent.altKey &&  zEvent.code === "KeyA") {
        lab15_1();
    }
} );

function checkForm() {
    if(!lab16.name.value) {
      alert("Имя не было введено.");
      lab16.name.focus();
	  return;
    } else {
	 var reg = /^Имя_Фамилия\s[А-Я]{1}[а-я]+_[А-Я]{1}[а-я]+$/m;
	 if(!reg.exec(lab16.name.value)){
	    alert("Имя введено неверно.");
        lab16.name.focus();
		return;
	 }
	}
    
	if(!f.group.value) {
          alert("Факультет и группа не были введены.");
          f.group.focus();
		  return;
    } else {
	var reg = new RegExp("^гр.:{1}\\s[А-Я]{1,3}-\\d{2}[a-я]{1}\\sс-т\\s[А-Я][а-я]+$", 'm');
	if(!f.group.value.match(reg)) {
        alert("Группа/студент введены неверно.");
        f.group.focus();
		return;
	 }
	}
	if(!f.num.value) {
      alert("Телефон не был введен.");
      f.num.focus();
	  return;
    } else {
	 var reg = /^Имя_Фамилия\s[А-Я]{1}[а-я]+_[А-Я]{1}[а-я]+$/m;
	 if(!f.num.value.match(f.num.pattern)) {
        alert("Телефон введен неверно.");
        f.num.focus();
		return;
	 } else if(confirm("Передача на сервер?")) f.submit();
	}
	}