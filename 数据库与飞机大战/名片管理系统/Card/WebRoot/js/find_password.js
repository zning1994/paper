// JavaScript Document
function CheckPassword_Confirm() {
	var password = document.getElementById("password").value;
	var password_confirm = document.getElementById("password_confirm").value;	
	if (password != (password_confirm)) {
		document.getElementById("password_confirmError").innerHTML = "<font style='color:red'>�����벻һ�£�</font>";
		return false;
	} else {
		document.getElementById("password_confirmError").innerHTML = "<font style='color:green'>��</font>";
		return true;
	}
}
function CheckPassword() {
	var password = document.getElementById("password").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(password)) {
		document.getElementById("passwordError").innerHTML = "<font style='color:red'>�����벻Ϊ�գ�</font>";
		return false;
	} else {
		document.getElementById("passwordError").innerHTML = "<font style='color:green'>��</font>";
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
			document.getElementById("emailError").innerHTML = tip;
		} else {
			alert("�������ҳ�����쳣!");
		}
	}
}
function sendRequest() {
	var email = document.getElementById("email").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(email)) {
		document.getElementById("emailError").innerHTML = "<font style='color:red'>�����䲻Ϊ��!</font>";
	} else {
		var url = "AjaxEmailServlet.action?email=" + email;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse;
		XMLHttpReq.send(null);
	}
}