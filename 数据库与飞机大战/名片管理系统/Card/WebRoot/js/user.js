// JavaScript Document
function select_all() { // ȫѡ
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
		window.location.href = "UserSelectServlet.action?all=1&&pageNow=1&&pageSize="
				+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "UserSelectServlet.action?all=1&&pageNow=" + num;
	}
}
function SetNum1() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "UserSelectServlet.action?all=0&&pageNow=1&&pageSize="
				+ num;
	}
}
function Jump1() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "UserSelectServlet.action?all=0&&pageNow=" + num;
	}
}
function Delete()
{
	document.formuser.submit();
}
function Select()
{
	window.location.href="user_select.jsp";
}