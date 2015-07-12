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
			document.getElementById("usernameerror").innerHTML = tip;
		} else {
			alert("您请求的页面有异常!");
		}
	}
}
function sendRequest() {
	var usersname = document.getElementById("username").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(usersname)) {
		document.getElementById("usernameerror").innerHTML = "<font style='color:red'>×用户名不为空!</font>";
	} else {
		var url = "AjaxUsersAlterServlet?username=" + usersname;
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
			document.getElementById("emailerror").innerHTML = tip;
		} else {
			alert("您请求的页面有异常!");
		}
	}
}
function sendRequest1() {
	var email = document.getElementById("email").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(email)) {
		document.getElementById("emailerror").innerHTML = "<font style='color:red'>×邮箱不为空！</font>";
	} else {
		var url = "AjaxEmailAlterServlet?email=" + email;
		createXMLHttpRequest();
		XMLHttpReq.open("GET", url, true);
		XMLHttpReq.onreadystatechange = processResponse1;
		XMLHttpReq.send(null);
	}
}