<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ page
	import="com.manager.entity.*,com.user.dao.*,com.user.dao.impl.*,com.manager.dao.*,com.manager.dao.impl.*"%>
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
<title>组详细信息</title>
<link href="css/table.css" rel="stylesheet" type="text/css" />
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
	font-size: 18px;
	font-weight: bold;
}
-->
</style>
  </head>
  
  <body>
  
   <div align="center">
   <p class="STYLE8">组详细信息<br/></p>
   <% 
   Groups g = (Groups)session.getAttribute("groupitem");
   GroupDao dao = new GroupDaoImpl();
   Users_PositionDao updao = new Users_PositionDaoImpl();
   UsersDao udao = new UsersDaoImpl();
   CompanyDao cd = new CompanyDaoImpl();
   DepartmentDao dd = new DepartmentDaoImpl();
   String fatherName = "";
   if(g.getFatherGroupId()!=0){
    	fatherName = dao.findById(g.getFatherGroupId());
   }
   List<Users_Position> list = updao.find("select * from users_position where usersid="+g.getUsersId());
   Users_Position up = list.get(0);
   System.out.println(up.getDepartmentId());
   %>
<table width="500" border="1" class="gridtable">
  <tr>
    <td width="30%" class="STYLE1">组名</td>
    <td width="70%" class="STYLE1"><%=g.getGroupName() %></td>
  </tr>
  <tr>
    <td class="STYLE1">所在父组</td>
    <td class="STYLE1"><%=fatherName %></td>
  </tr>
  <tr>
    <td class="STYLE1">所在公司</td>
    <td class="STYLE1"><%=cd.findById(up.getCompanyId()) %></td>
  </tr>
  <tr>
    <td class="STYLE1">所在部门</td>
    <td class="STYLE1"><%=dd.findById(up.getDepartmentId()) %></td>
  </tr>
  <tr>
    <td class="STYLE1">共享范围</td>
    <td class="STYLE1"><%if(g.getSharing()==1){%>
    全部共享
    <%}else if(g.getSharing()==2){ %>
  公司内共享
    <%}else if(g.getSharing()==3){ %>
    部门内共享
    <%}%>
    </td>
  </tr>
  <tr>
    <td class="STYLE1">简介</td>
    <td class="STYLE1"><textarea cols="40" row="5" readonly><%=g.getNotes() %></textarea></td>
  </tr>
  <tr>
    <td class="STYLE1">创建者</td>
    <td class="STYLE1"><%=udao.findById(g.getUsersId()) %></td>
  </tr>
  <tr>
    <td class="STYLE1">创建时间</td>
    <td class="STYLE1"><%=g.getCreateTime().toLocaleString().split(" ")[0] %></td>
  </tr>
  <tr>
    <td class="STYLE1">查看组中名片</td>
    <td class="STYLE1"><a href="Group_CardServlet.action?groupId=<%=g.getGroupId() %>">查看</a></td>
  </tr>
</table>
<%session.removeAttribute("groupitem"); %>
</div>
  </body>
</html>
