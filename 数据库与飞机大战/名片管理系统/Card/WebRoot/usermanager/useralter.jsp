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
    
    <title>用户信息修改</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
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
<link href="css/table.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" language="javascript" src="js/users.js" charset="gbk"></script>
<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript">
    		$(function(){
				$("#company").change(function(){
        			var sup = document.formusersalter.company.value;
        			$.post("ajaxCompany",{"company":sup},function(response, suatus){
		       			var rs = response.split("-");
		       			var n = document.getElementById("department").length;
		       			document.getElementById("department").length=0;
		       			for(var i=0; i<rs.length; i++){
		       				var op = new Option(rs[i]);
		   					document.getElementById("department").add(op);
		   				}
		       		});
				});
    		});
		</script>
		<script type="text/javascript">
    		$(function(){
				$("#department").change(function(){
        			var sup = document.formusersalter.company.value;
        			var sup1 = document.formusersalter.department.value;
        			$.post("ajaxDepartment",{"company":sup,"department":sup1},function(response, suatus){
		       			var rs = response.split("-");
		       			var n = document.getElementById("position").length;
		       			document.getElementById("position").length=0;
		       			for(var i=0; i<rs.length; i++){
		       				var op = new Option(rs[i]);
		   					document.getElementById("position").add(op);
		   				}
		       		});
				});
    		});
		</script>
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
  <br/>
  <br/>
  <form action="UsersAlterServlet.action" method="post" name="formusersalter">
  <table  class="gridtable" width="70%" height="245" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9" align="center">
  <tr>
    <td colspan="2" align="center"><span class="STYLE8">个人信息修改</span></td>
  </tr>
  <tr>
        <td width="30%" height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">用户名</span></div></td>
        <td width="70%" height="22" bgcolor="#FFFFFF">
          <input type="text" name="username" id="username"  class="STYLE2" value="<%=u.getUsersName() %>" onblur="sendRequest()"/><span id="usernameerror" class="STYLE1"></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">邮箱</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><input type="text" name="email" id="email"  class="STYLE2" value="<%=u.getEmail() %>" onblur="sendRequest1()"/><span id="emailerror"></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">公司</span></div></td>
        <td height="22" bgcolor="#FFFFFF">
        <select  name="company" id="company" class="STYLE2" >
          <option selected><%=company %></option>
          <%
          List<Company> list3  = cd.find("select * from company where companyId not in ("+up.getCompanyId()+")");
          for(int i=0;i<list3.size();i++)
          {
          Company com = list3.get(i);
           %>
           <option><%=com.getCompanyName() %></option>
           <%} %>
          </select>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">部门</span></div></td>
        <td height="22" bgcolor="#FFFFFF">
        <select  name="department" id="department" class="STYLE2" >
          <option selected><%=department%></option>
        </select> 
        </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="table STYLE1">职位</span></div></td>
        <td height="22" bgcolor="#FFFFFF">
        <select  name="position" id="position" class="STYLE2" >
          <option selected><%=position%></option>
        </select>
        </tr>
     <tr>
        <td height="30" bgcolor="#FFFFFF" colspan="2"><div align="center">
          <p>
            <input type="submit" name="修改" value="修改" id="button">
            <input type="reset" name="重置" value="重置" id="button" />
          </p>
		</div>       
		</td>
      </tr>
    </table>
    </form>
  </body>
</html>
