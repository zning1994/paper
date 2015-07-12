<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ page
	import="com.manager.entity.*,com.manager.dao.*,com.manager.dao.impl.*"%>
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
	<style type="text/css">
<!--
body{background:url(images/backgraund.jpg) repeat;}
#button{
background:url(button1.jpg);
width:88px;
height:30px;
font-size:18px;
}
.STYLE1 {font-size: 18px}
.STYLE2 { width:200px; height:21px; margin-left:15px;margin-right:160px;}
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
<link href="css/table.css" rel="stylesheet" type="text/css" />

  </head>
  <body>
  <%
    Users u = (Users)session.getAttribute("users");
    UsersDao dao = new UsersDaoImpl();
    Users_PositionDao updao = new Users_PositionDaoImpl();
    List<Users> list = dao.find("select * from Users where usersId="+u.getUsersId());
    List<Users_Position> list1 = updao.find("select * from Users_Position where usersId="+u.getUsersId());
    Users user = list.get(0);
    Users_Position up = list1.get(0);
    CompanyDao cd = new CompanyDaoImpl();
    DepartmentDao dd = new DepartmentDaoImpl();
    PositionDao pd = new PositionDaoImpl();
    String company = cd.findById(up.getCompanyId());
    String department = dd.findById(up.getDepartmentId());
    String position = pd.findById(up.getPositionId());
   %>
  <br/><br/>
    <table  class="gridtable" width="59%" height="245" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9" align="center">
  <tr>
    <td colspan="2" align="center"><span class="STYLE8">个人信息</span></td>
  </tr>
  <tr>
        <td width="30%" height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">用户名</span></div></td>
        <td width="70%" height="22" bgcolor="#FFFFFF"><span class="STYLE1"><%=user.getUsersName() %></span>
        </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">邮箱</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><span class="STYLE1"><%=user.getEmail() %></span>     </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">公司</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><span class="STYLE1"><%=company %></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">部门</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><span class="STYLE1"><%=department %></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">职位</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><span class="STYLE1"><%=position %></span>      </tr>
</table>
  </body>
</html>
