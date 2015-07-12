function Check()
{
	var usersname = document.getElementById("usernameS2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(usersname)) {
		document.getElementById("usernameS2error").innerHTML = "<font style='color:red'>×用户名不为空!</font>";
		return false;
	} else {
		document.getElementById("usernameS2error").innerHTML = "<font style='color:green'>√</font>";
	}
	var address = document.getElementById("homeaddress2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(address)) {
		alert(address);
		document.getElementById("homeaddress2error").innerHTML = "<font style='color:red'>×地址不为空!</font>";
		return false;
	} else {
		document.getElementById("homeaddress2error").innerHTML = "<font style='color:green'>√</font>";
	}
	var postcode2 = document.getElementById("postcode2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(postcode2)) {
		document.getElementById("postcode2error").innerHTML = "<font style='color:red'>×邮箱不为空!</font>";
		return false;
	} else {
		document.getElementById("postcode2error").innerHTML = "<font style='color:green'>√</font>";
	}
	var tel2 = document.getElementById("tel2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(tel2)) {
		document.getElementById("tel2error").innerHTML = "<font style='color:red'>×电话不为空!</font>";
		return false;
	} else {
		document.getElementById("tel2error").innerHTML = "<font style='color:green'>√</font>";
	}
	var mailbox2 = document.getElementById("mailbox2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(mailbox2)) {
		document.getElementById("mailbox2error").innerHTML = "<font style='color:red'>×邮箱不为空!</font>";
		return false;
	} else {
		document.getElementById("mailbox2error").innerHTML = "<font style='color:green'>√</font>";
	}
	var myfile = document.getElementById("myFile").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(myfile)) {
		document.getElementById("myFileerror").innerHTML = "<font style='color:red'>×路径不为空!</font>";
		return false;
	} else {
		document.getElementById("myFileerror").innerHTML = "<font style='color:green'>√</font>";
	}
	var myfile2 = document.getElementById("myFile2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(myfile2)) {
		document.getElementById("myFile2error").innerHTML = "<font style='color:red'>×路径不为空!</font>";
		return false;
	} else {
		document.getElementById("myFile2error").innerHTML = "<font style='color:green'>√</font>";
	}
	return true;
}
function Check1()
{
	var usersname = document.getElementById("usernameS").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(usersname)) {
		document.getElementById("usernameSerror").innerHTML = "<font style='color:red'>×用户名不为空!</font>";
		return false;
	} else {
		document.getElementById("usernameSerror").innerHTML = "<font style='color:green'>√</font>";
	}
	var address = document.getElementById("homeaddress2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(address)) {
		document.getElementById("homeaddresserror").innerHTML = "<font style='color:red'>×地址不为空!</font>";
		return false;
	} else {
		document.getElementById("homeaddresserror").innerHTML = "<font style='color:green'>√</font>";
	}
	var postcode2 = document.getElementById("postcode").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(postcode2)) {
		document.getElementById("postcodeerror").innerHTML = "<font style='color:red'>×邮箱不为空!</font>";
		return false;
	} else {
		document.getElementById("postcodeerror").innerHTML = "<font style='color:green'>√</font>";
	}
	var tel2 = document.getElementById("tel").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(tel2)) {
		document.getElementById("telerror").innerHTML = "<font style='color:red'>×电话不为空!</font>";
		return false;
	} else {
		document.getElementById("telerror").innerHTML = "<font style='color:green'>√</font>";
	}
	var mailbox2 = document.getElementById("mailbox2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(mailbox2)) {
		document.getElementById("mailboxerror").innerHTML = "<font style='color:red'>×邮箱不为空!</font>";
		return false;
	} else {
		document.getElementById("mailboxerror").innerHTML = "<font style='color:green'>√</font>";
	}
	var myfile = document.getElementById("myFile").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(myfile)) {
		document.getElementById("myFileerror").innerHTML = "<font style='color:red'>×路径不为空!</font>";
		return false;
	} else {
		document.getElementById("myFileerror").innerHTML = "<font style='color:green'>√</font>";
	}
	var myfile2 = document.getElementById("myFile2").value;
	var pattern = /^\s{0,}$/;
	if (pattern.test(myfile2)) {
		document.getElementById("myFile2error").innerHTML = "<font style='color:red'>×路径不为空!</font>";
		return false;
	} else {
		document.getElementById("myFile2error").innerHTML = "<font style='color:green'>√</font>";
	}
	return true;
}