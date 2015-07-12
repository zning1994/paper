<%@ page language="java" import="java.util.*,com.manager.entity.*" pageEncoding="utf-8"%>
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
<title>增加新名片</title>
<link rel="stylesheet" type="text/css" href="style5.css" />
<link href="css/table.css" rel="stylesheet" type="text/css" />
<script language="javascript" src="js/card.js"></script>
<style type="text/css">
<!--
body{background:url(images/backgraund.jpg) repeat;}
#button{
background:url(images/button1.jpg);
width:50px;
height:25px;
font-size:15px;
}
.STYLE1 {font-size: 15px}
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
	font-size: 22px;
	font-weight: bold;
	margin-left:300px;
}
#Layer1 {
	position:absolute;
	left:350px;
	top:35px;
	width:447px;
	height:373px;
	z-index:1;
}
#Layer2 {
	position:absolute;
	left:11px;
	top:34px;
	width:424px;
	height:387px;
	z-index:2;
}
-->
</style>
  </head>
  
  <body>
  <br/>
  <p  class="STYLE8">详细信息</p>
  <%Card card = (Card)request.getAttribute("card"); 
  	Card_Users cu = (Card_Users)request.getAttribute("card_users");
  	String username = (String) request.getAttribute("username");
  	String companyname = (String) request.getAttribute("companyname");
  	String departmentname = (String) request.getAttribute("departmentname");
  	String position = (String) request.getAttribute("position");
  	String front = (String) request.getAttribute("front");
  	String behind = (String) request.getAttribute("behind");
  session.setAttribute("cardId",card.getCardId());
  
  %>
 <form action="cardmanage/collect_add.jsp" name="cardinfo" id="cardinfo">
  <div id="Layer1">
    <div class="scan-right">
      <p>&nbsp;</p>
      <table width="400" border="1" class="gridtable">
          <tr>
            <td width="85" class="STYLE1">姓名： </td>
            <td width="193" class="STYLE1"><%=cu.getCardUsersName()%></td>
          </tr>
          <tr>
            <td class="STYLE1">所在公司：</td>
            <td class="STYLE1"><%=companyname %></td>
          </tr>
          <tr>
            <td class="STYLE1">所在部门：</td>
            <td class="STYLE1"><%= departmentname%></td>
          </tr>
          <tr>
            <td class="STYLE1">职位：</td>
            <td class="STYLE1"><%=position%></td>
          </tr>
          <tr>
            <td class="STYLE1">家庭住址：</td>
            <td class="STYLE1"><%=cu.getAddress() %></td>
          </tr>
          <tr>
            <td class="STYLE1">邮编：</td>
            <td class="STYLE1"><%=cu.getPostCode() %></td>
          </tr>
          <tr>
            <td class="STYLE1">联系电话：</td>
            <td class="STYLE1"><%=cu.getTel() %></td>
          </tr>
          <tr>
            <td class="STYLE1">邮箱：</td>
            <td class="STYLE1"><%=cu.getEmail() %></td>
          </tr>
          <tr>
            <td class="STYLE1">备注：</td>
            <td class="STYLE1"><!--<textarea name="textarea" cols="20" rows="3" readonly></textarea>-->
            					<%=card.getNotes() %></td>
          </tr>
          <tr>
            <td class="STYLE1">查看权限：</td>
            <td class="STYLE1"><%int state=card.getState(); 
            if(state==1)
            out.print("全部共享");
            else if(state==2)
            out.print("公司内共享");
            else if(state==3)
            out.print("部门内共享");
            %></td>
          </tr>
          <tr>
            <td class="STYLE1">创建者：</td>
            <td class="STYLE1"><%=username %></td>
          </tr>
          <tr>
            <td class="STYLE1">创建日期：</td>
            <td class="STYLE1"><%=card.getCreateTime().toLocaleString().split(" ")[0] %></td>
          </tr>
          <tr>
            <td colspan="2" align="center"> <input type="button" value="收藏" onClick="Collect()"/></td>
          </tr>
        </table>
      <p align="justify">&nbsp; </p>
    </div>
  </div>
  <div id="Layer2">
    <div class="scan-right">
    <br/>
      <p>正面： </p>
      <table width="313" border="1" class="gridtable">
          <tr>
            <td width="303" height="191"><img src="http://localhost:8080/temp/<%=front %>" />
            </td>
          </tr>
        </table>
      背面：
      <table width="312" height="181" border="1" class="gridtable">
          <tr>
            <td width="302" height="175"><img src="http://localhost:8080/temp/<%=behind %>" /></td>
          </tr>
        </table>
    </div>
  </div>
  </body>
</html>
