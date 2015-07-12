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
		window.location.href = "CompanySelectServlet.action?all=1&&pageNow=1&&pageSize="+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "CompanySelectServlet.action?all=1&&pageNow=" + num;
	}
}
function SetNum1() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "CompanySelectServlet.action?all=0&&pageNow=1&&pageSize="+ num;
	}
}
function Jump1() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "CompanySelectServlet.action?all=0&&pageNow=" + num;
	}
}
function Delete()
{
	document.formcompany.submit();
}
function Select()
{
	window.location.href="company_select.jsp";
}
function Add()
{
	window.location.href="company_add.jsp";
}
function checkName()
{
	var companyname = document.getElementById("companyname").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(companyname)) {
		document.getElementById("companynameerror").innerHTML = "<font style='color:red'>×公司名不为空！</font>";
		return false;
	} else {
		document.getElementById("companynameerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function checkAddress()
{
	var companyaddress = document.getElementById("address1").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(companyaddress)) {
		document.getElementById("companyaddresserror").innerHTML = "<font style='color:red'>×地址不为空！</font>";
		return false;
	} else {
		document.getElementById("companyaddresserror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function checkTel()
{
	var companytel = document.getElementById("tel").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(companytel)) {
		document.getElementById("companytelerror").innerHTML = "<font style='color:red'>×联系方式不为空！</font>";
		return false;
	} else {
		document.getElementById("companytelerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function checkFax()
{
	var companyfax = document.getElementById("fax").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(companyfax)) {
		document.getElementById("companyfaxerror").innerHTML = "<font style='color:red'>×传真不为空！</font>";
		return false;
	} else {
		document.getElementById("companyfaxerror").innerHTML = "<font style='color:green'>√</font>";
		return true;
	}
}
function Check()
{
	if(checkName())
		if(checkAddress())
			if(checkTel())
				if(checkFax())
					return true;
	return false;
}