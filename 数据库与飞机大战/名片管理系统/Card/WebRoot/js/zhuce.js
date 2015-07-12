// JavaScript Document
function CheckPassword_Confirm() {
	var password = document.getElementById("passwordsignup").value;
	var password_confirm = document.getElementById("passwordsignup_confirm").value;
	if (password != (password_confirm)) {
		document.getElementById("passwordsignup_confirmError").innerHTML = "<font style='color:red'>×密码不一致！</font>";
		return false;
	} else {
		document.getElementById("passwordsignup_confirmError").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function checkPassword() {
	var password = document.getElementById("passwordsignup").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(password)) {
		document.getElementById("passwordsignupError").innerHTML = "<font style='color:red'>×密码不为空！</font>";
		return false;
	} else {
		document.getElementById("passwordsignupError").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
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
			document.getElementById("usernamesignupError").innerHTML = tip;
		} else {
			alert("您请求的页面有异常!");
		}
	}
}
function sendRequest() {
	var usersname = document.getElementById("usernamesignup").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(usersname)) {
		document.getElementById("usernamesignupError").innerHTML = "<font style='color:red'>×用户名不为空!</font>";
	} else {
		var url = "ajaxUsers?usernamesignup=" + usersname;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse;
		XMLHttpReq.send(null);
	}
}
function processResponse1() {
	if (XMLHttpReq.readyState == 4) {
		if (XMLHttpReq.status == 200) {
			var tip = XMLHttpReq.responseText;
			document.getElementById("emailsignupError").innerHTML = tip;
		} else {
			alert("您请求的页面有异常!");
		}
	}
}
function sendRequest1() {
	var email = document.getElementById("emailsignup").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(email)) {
		document.getElementById("emailsignupError").innerHTML = "<font style='color:red'>×邮箱不为空！</font>";
	} else {
		var url = "ajaxEmail?emailsignup=" + email;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse1;
		XMLHttpReq.send(null);
	}
}
function Check()
{
	if(CheckPassword_Confirm())
		if(checkPassword())
			return true;
	return false;
}