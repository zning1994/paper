<%@ page language="java" import="java.util.*" pageEncoding="utf-8" isErrorPage="true"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'error.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
  <body>
    <table width="508" height="296" border="0" align="center">
  <tr>
    <td width="624" height="292" align="center" background="images/behind.jpg">
      <label></label>
	  <br /><br /><br /><br /><br /><br /><br />
      <form style="margin-left:100px">
      <br/>
	  <a href="javascript:history.go(-1)" >返回</a>
	  </form>
	  </td>
  </tr>
</table>
  </body>
</html>
