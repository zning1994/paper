<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
<%@ page import="java.sql.*,com.manager.dao.*,com.manager.dao.impl.*,com.manager.entity.*,com.manager.util.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>名片管理系统</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<link href="css/main.css" rel="stylesheet" type="text/css" />

  </head>
 <%session = request.getSession();
   Users u = (Users)session.getAttribute("users"); 
   //java.util.Date d = u.getLastLogin();%>
  <body>
    <div id="top">
	      <div id="logo"></div>
		  <div id="user"><marquee width="100%">欢迎您:<%=u.getUsersName() %>IP:<%=request.getRemoteAddr() %></marquee></div>	 
	 </div>
  </body>
</html>
