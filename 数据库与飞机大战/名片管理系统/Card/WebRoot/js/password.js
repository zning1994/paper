// JavaScript Document
function CheckPassword_Confirm() {
	var password = document.getElementById("password").value;
	var password_confirm = document.getElementById("password_confirm").value;	
	if (password != (password_confirm)) {
		document.getElementById("password_confirmerror").innerHTML = "<font style='color:red'>×密码不一致！</font>";
		return false;
	} else {
		document.getElementById("password_confirmerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function CheckPassword() {
	var password = document.getElementById("password").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(password)) {
		document.getElementById("passworderror").innerHTML = "<font style='color:red'>×密码不为空！</font>";
		return false;
	} else {
		document.getElementById("passworderror").innerHTML = "<font style='color:green'>√</font>";
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
			document.getElementById("oldpassworderror").innerHTML = tip;
		} else {
			alert("您请求的页面有异常!");
		}
	}
}
function CheckOldPassword() {
	var oldpassword = document.getElementById("oldpassword").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(oldpassword)) {
		document.getElementById("oldpassworderror").innerHTML = "<font style='color:red'>×密码不为空!</font>";
	} else {
		var url = "AjaxPasswordServlet?oldpassword=" + oldpassword;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse;
		XMLHttpReq.send(null);
	}
}