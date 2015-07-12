<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ page import="com.manager.entity.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" 

"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title></title>
<meta charset="utf-8">
<link rel="stylesheet" type="text/css" media="screen" href="css/reset.css">
<link rel="stylesheet" type="text/css" media="screen" href="css/style.css">
<script type="text/javascript" src="js/jquery-1.6.1.min.js"></script>
</head>

<body>
	 <!--==============================header=================================-->
  <div class="main">
    <!--==============================header=================================-->
    <header>
      <div class="headtitle" ><font face="verdana" size="+4">名片管理系统
<%Users u =(Users) session.getAttribute("users"); %>
</font></h1></div>
      <div class="login"><%=u.getUsersName() %>&nbsp;&nbsp;&nbsp;登录时间<%=u.getLastLogin().toLocaleString() %>&nbsp;&nbsp;&nbsp;<a href="LeaveServlet.action"><font color="#000000">退出</font></a></div>
      <p class="logo" href="index.html">HomeStyle</p>
      <nav>
        <ul class="menu">
          <li><a class="main1" href="content.jsp" target="body">首页 </a></li>
        </ul>
        <div class="clear"></div>
        <div class="clear"></div>
      </nav>

      <div class="clear"></div>
    </header>
    <div class="clear"></div>
    <!--==============================content================================-->

  </div>
</body>
</html>
