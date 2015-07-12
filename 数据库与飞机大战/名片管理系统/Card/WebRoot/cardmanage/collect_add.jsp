<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ page
	import="com.manager.entity.*,com.user.dao.*,com.user.dao.impl.*"%>
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
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<script type="text/javascript" language="javascript" src="js/group.js" charset="gbk"></script>
<title>新建组</title>
<link href="css/table.css" rel="stylesheet" type="text/css" />
<style type="text/css">
<!--
body{background:url(images/backgraund.jpg) repeat;}
#button{
background:url(images/button1.jpg);
width:88px;
height:30px;
font-size:18px;
}
.STYLE1 {font-size: 18px}
.STYLE2 { width:200px; height:21px; margin-left:15px;}
.STYLE3 {width:204px;height:26px;margin-left:15px;margin-right:160px;}
.button{background: transparent url('images/button.jpg');     color: #444;     font-family:"Microsoft YaHei",微软雅黑,"MicrosoftJhengHei",华文细黑,STHeiti,MingLiu; font-weight:300;   height: 24px; margin-left:30px;  margin-right: 10px;     padding-right: 18px;      text-decoration: none; 
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
  </head>
  <% int cardId = (Integer)session.getAttribute("cardId"); %>
 <body background="images/backgraund.jpg">
<div align="center">
<form action="CollectionAddServlet.action" method="post" >
<p class="STYLE8">收藏名片<br />  
  </p>
<table width="600" border="1" class="gridtable" >
  <tr>
    <td width="87" class="STYLE1">名片编号</td>
    <td width="294"><%=cardId %></td>
    <% session.setAttribute("cardId",cardId); %>
  </tr>
  <tr>
    <td class="STYLE1">简介</td>
    <td><textarea cols="50" row="5" name="note" id="note"></textarea></td>
  </tr>
  <tr>
        <td height="30" bgcolor="#FFFFFF" colspan="2"><div align="center">
          <p>
            <input type="submit" name="添加" value="添加" id="button">
            <input type="reset" name="重置" value="重置" id="button" />
          </p>
		</div>       
		</td>
      </tr>
</table>
</form>
</div>
</body>
</html>
