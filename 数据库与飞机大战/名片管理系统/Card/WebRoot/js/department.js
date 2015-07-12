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
		window.location.href = "DepartmentSelectServlet.action?all=1&&pageNow=1&&pageSize="+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "DepartmentSelectServlet.action?all=1&&pageNow=" + num;
	}
}
function SetNum1() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "DepartmentSelectServlet.action?all=0&&pageNow=1&&pageSize="+ num;
	}
}
function Jump1() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "DepartmentSelectServlet.action?all=0&&pageNow=" + num;
	}
}
function Delete()
{
	document.formdepartment.submit();
}
function Select()
{
	window.location.href="department_select.jsp";
}
function Add()
{
	window.location.href="department_add.jsp";
}
function checkName()
{
	var departmentname = document.getElementById("departmentname").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(departmentname)) {
		document.getElementById("departmentnameerror").innerHTML = "<font style='color:red'>×部门名不为空！</font>";
		return false;
	} else {
		document.getElementById("departmentnameerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function checkTel()
{
	var departmenttel = document.getElementById("tel").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(departmenttel)) {
		document.getElementById("departmenttelerror").innerHTML = "<font style='color:red'>×联系方式不为空！</font>";
		return false;
	} else {
		document.getElementById("departmenttelerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function Check()
{
	if(checkName())
		if(checkTel())
			return true;
	return false;
}