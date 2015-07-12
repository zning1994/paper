// JavaScript Document
var XMLHttpReq;
function createXMLHttpRequest() {
	if (window.XMLHttpRequest) {
		XMLHttpReq = new XMLHttpRequest();
	} else if (window.ActiveXObject) {
		try {
			XMLHttpReq = new ActiveXobject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
				XMLHttpReq = new ActiveXobject("Microsoft.XMLHTTP");
			} catch (e) {
			}
		}
	}
}
function processResponse() {
	if (XMLHttpReq.readyState == 4) {
		if (XMLHttpReq.status == 200) {
			var tip = XMLHttpReq.responseText;
			document.getElementById("groupnameerror").innerHTML = tip;
		} else {
			alert("您请求的页面有异常!");
		}
	}
}
function CheckName() {
	var groupname = document.getElementById("groupname").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(groupname)) {
		document.getElementById("groupnameerror").innerHTML = "<font style='color:red'>×组名不为空!</font>";
	} 
	else {
		var url = "AjaxGroupServlet?groupname=" + groupname;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse;
		XMLHttpReq.send(null);
	}
}
function CheckName1() {
	var groupname = document.getElementById("groupname").value;
	alert(groupname);
	var oldgroupname = document.getElementById("oldgroupname").value;
	alert(oldgroupname);
	var pattern = /^\s{0,}$/;
	if (pattern.test(groupname)) {
		alert(groupname);
		document.getElementById("groupnameerror").innerHTML = "<font style='color:red'>×组名不为空!</font>";
	} 
	else {
		var url = "AjaxGroupAlterServlet?groupname=" + groupname+"&&oldgroupname="+oldgroupname;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse;
		XMLHttpReq.send(null);
	}
}
function select_all() { // 全选
	var inputs = document.getElementsByTagName("input");
	var str = document.getElementById("all");
	for ( var i = 0; i < inputs.length; i++) {
		if (inputs[i].getAttribute("name") == "delete") {
			if (str.checked) {
				inputs[i].checked = true;
			} else {
				inputs[i].checked = false;
			}
		}
	}
}
function SetNum() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "GroupSelectServlet.action?pageNow=1&&pageSize="
				+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "GroupSelectServlet.action?pageNow=" + num;
	}
}
function SetNum1() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "GroupSelfServlet.action?pageNow=1&&pageSize="+ num;
	}
}
function Jump1() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "GroupSelfServlet.action?pageNow=" + num;
	}
}
function Delete()
{
	document.formself.submit();
}
function Daochu()
{
	document.formscan.submit();
}
function Daochu1()
{
	document.getElementById("formself").action = "GroupExcelServlet.action";
	document.formself.submit();
}
function processResponse1() {
	if (XMLHttpReq.readyState == 4) {
		if (XMLHttpReq.status == 200) {
			clearSuggest();
			var tips = XMLHttpReq.responseXML.getElementsByTagName("res");
			if(tips.length!=0)
			{
				for(i=0;i<tips.length;i++)
				{
					title = tips[i].firstChild.nodeValue;
					alert(title);
					createSuggest();
				}
				displaySuggest();
			}
			else
			{
				clearSuggest();
				hiddenSuggest();
			}
			alert(title);
		} else {
			window.alert("您请求的页面有异常!");
		}
	}
}
function createSuggest()
{
	var sDiv="<div class='out'onmouseover='mover(this);'onmouseout='mout(this);'onclick='setSuggest(this)'>"+title+"</div>";
	document.getElementById("suggest").innerHTML+=sDiv;
}
function setSuggest(para)
{
	document.getElementById("title").value = para.firstChild.nodeValue;
	hiddenSuggest();
}
function mover(para)
{
	para.className="over";
}
function mout(para)
{
	para.className="out";
}
function displaySuggest()
{
	document.getElementById("suggest").style.display="block";
	document.getElementById("suggest").style.width=document.getElementById("title").clientWidth+4;
	document.getElementById("suggest").style.left=document.getElementById("title").offsetLeft+73;
	document.getElementById("suggest").style.top=document.getElementById("title").style.top+79;
}
function clearSuggest()
{
	document.getElementById("suggest").innerHTML="";
}
function hiddenSuggest()
{
	document.getElementById("suggest").style.display="none";
}
function sendRequest()
{
	var info = document.getElementById("title").value;
	var url = "SuggestServlet?info="+info;
	createXMLHttpRequest();
	XMLHttpReq.open("GET", url,true);
	XMLHttpReq.onreadystatechange=processResponse1;
	XMLHttpReq.send(null);
}
