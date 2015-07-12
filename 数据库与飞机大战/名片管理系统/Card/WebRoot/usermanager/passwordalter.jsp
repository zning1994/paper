<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<script type="text/javascript" language="javascript" src="js/password.js" charset="gbk"></script>
	<style type="text/css">
<!--
body{background:url(images/backgraund.jpg) repeat;}
#button{
background:url(images/button1.jpg);
width:88px;
height:30px;
font-size:18px;
}
.STYLE1 {font-size: 18px;font-weight:bold;}
.STYLE2 { width:200px; height:21px; margin-left:15px;}
.STYLE3 {width:204px;height:26px;margin-left:15px;margin-right:160px;}
.button{background: transparent url('images/button.jpg');     color: #444;     font-

family:"Microsoft YaHei",微软雅黑,"MicrosoftJhengHei",华文细黑,STHeiti,MingLiu; font-

weight:300;   height: 24px; margin-left:30px;  margin-right: 10px;     padding-right: 

18px;      text-decoration: none; 
}
body {
	margin-top: 0px;
	margin-bottom: 0px;
}
.STYLE7 {font-size: 12px;}
.STYLE8 {
	font-size: 30px;
	font-weight: bold;
}
-->
</style>
<link href="css/table.css" rel="stylesheet" type="text/css" />

  </head>
  
  <body>
  <br/>
  <br/>
  <form action="PasswordAlterServlet.action" method="post">
   <table  class="gridtable" width="70%" height="245" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9" align="center">
  <tr>
    <td colspan="2" align="center"><span class="STYLE8">修改密码</span></td>
  </tr>
      <tr>
        <td width="40%" height="22" bgcolor="#FFFFFF"><div align="center"><span 

class="table STYLE1">原密码</span></div></td>
        <td width="60%" height="22" bgcolor="#FFFFFF">
          <input type="password" name="oldpassword" id="oldpassword" class="STYLE2" onblur="CheckOldPassword()"/>
          <span id="oldpassworderror"></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table 

STYLE1">新密码</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><input type="password" name="password"  id="password"
class="STYLE2" onblur="CheckPassword()"/>
<span id="passworderror"></span>
      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table 

STYLE1">确认新密码</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><input type="password" name="password_confirm"  id="password_confirm"  
class="STYLE2" onblur="CheckPassword_Confirm()"/><span id="password_confirmerror"></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF" colspan="2">
		<p align="center">
		<input type="submit" name="修改" value="修改" id="button" />
         <input type="reset" name="重置" value="重置" id="button" />
		  </p></td>
  </tr>
</table>
</form>
  </body>
</html>
