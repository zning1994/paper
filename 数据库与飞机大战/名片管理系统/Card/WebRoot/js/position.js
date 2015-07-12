// JavaScript Document
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
		window.location.href = "PositionSelectServlet.action?all=1&&pageNow=1&&pageSize="+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "PositionSelectServlet.action?all=1&&pageNow=" + num;
	}
}
function SetNum1() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "PositionSelectServlet.action?all=0&&pageNow=1&&pageSize="+ num;
	}
}
function Jump1() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "PositionSelectServlet.action?all=0&&pageNow=" + num;
	}
}
function Delete()
{
	alert("aaaaa");
	document.formposition.submit();
}
function Select()
{
	window.location.href="position_select.jsp";
}
function Add()
{
	window.location.href="position_add.jsp";
}
function checkName()
{
	var positionname = document.getElementById("positionname").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(positionname)) {
		document.getElementById("positionnameerror").innerHTML = "<font style='color:red'>×职务名不为空！</font>";
		return false;
	} else {
		document.getElementById("positionnameerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function Check()
{
	if(checkName())
		return true;
	elde 
	    return false;
}