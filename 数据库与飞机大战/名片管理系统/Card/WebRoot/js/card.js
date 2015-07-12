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
		window.location.href = "CardSelectServlet.action?pageNow=1&&pageSize="
				+ num;
	}
}
function Jump() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "CardSelectServlet.action?pageNow=" + num;
	}
}
function SetNum1() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "CardSelfServlet.action?pageNow=1&&pageSize="+ num;
	}
}
function Jump1() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "CardSelfServlet.action?pageNow=" + num;
	}
}
function SetNum2() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "Group_CardServlet.action?pageNow=1&&pageSize="+ num;
	}
}
function Jump2() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "Group_CardServlet.action?pageNow=" + num;
	}
}
function SetNum3() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "Group_CardServlet.action?self=1&&pageNow=1&&pageSize="+ num;
	}
}
function Jump3() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "Group_CardServlet.action?self=1&&pageNow=" + num;
	}
}
function SetNum4() {
	var num = document.getElementById("pageSize").value;
	if (num > 0) {
		window.location.href = "CollectionSelectServlet.action?pageNow=1&&pageSize="+ num;
	}
}
function Jump4() {
	var num = document.getElementById("jump").value;
	if (num > 0) {
		window.location.href = "CollectionSelectServlet.action?pageNow=" + num;
	}
}
function Delete1()
{
	document.formcard_group.submit();
}
function Delete2()
{
	document.formcollect.submit();
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
	document.getElementById("formself").action = "CardExcelServlet.action";
	document.formself.submit();
}
function Collect()
{
	document.cardinfo.submit();
}
function AddInGroup()
{
	document.getElementById("formself").action = "AddInGroupServlet.action";
	document.formself.submit();
}