// JavaScript Document
function SetNum() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "PowerSelectServlet.action?pageNow=1&&pageSize="+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "PowerSelectServlet.action?pageNow=" + num;
	}
}
function checkName()
{
	var powername = document.getElementById("powername").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(powername)) {
		document.getElementById("powernameerror").innerHTML = "<font style='color:red' size='-1'>×权限名不为空！</font>";
		return false;
	} else {
		document.getElementById("powernameerror").innerHTML = "<font style='color:green' size='-1'>√</font>";
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