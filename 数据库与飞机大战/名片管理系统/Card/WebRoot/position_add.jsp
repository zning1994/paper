<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
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
    
    <title>添加部门</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<link href="css/main.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" language="javascript" src="js/position.js"
			charset="gbk"></script>
	<script type="text/javascript" src="js/jquery.js"></script>
	<style type="text/css">
<!--
.STYLE1 {font-size: 18px}
.STYLE2 { width:200px; height:30px; margin-left:40px;}
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
	font-weight:normal;
}
-->
</style>
<script type="text/javascript">
    		$(function(){
				$("#company").change(function(){
        			var sup = document.form_position.company.value;
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
  </head>
  
  <body>
   <div id="right_font"><img src="images/main_14.gif"/> 您现在所在的位置：首页 →职务管理 →添加新职务 </div>
   <form action="PositionAddServlet.action" method="post" name="form_position" onSubmit="return Check()">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <th  align="center"><p class="STYLE8">添加职务</p>
    </th>
  </tr>
  <tr>
    <td><table width="52%" height="245" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9" align="center">
        <td width="25%" height="50" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">公司名称</span></div></td>
        <td width="68%" height="50" bgcolor="#FFFFFF">
          <select  name="companyname" id="company" class="STYLE2" >
          <%
          CompanyDao cd = new CompanyDaoImpl();
          List<Company> list  = cd.find("select * from company");
          for(int i=0;i<list.size();i++)
          {
          Company company = list.get(i);
           %>
           <option ><%=company.getCompanyName() %></option>
           <%} %>
          </select>       </tr>
		   <tr>
        <td height="50" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">部门名称</span></div></td>
        <td height="50" bgcolor="#FFFFFF">  <select  name="departmentname" id="department" class="STYLE2" >
        <%
          DepartmentDao dd = new DepartmentDaoImpl();
          List<Department> list1  = dd.find("select * from department where companyId = 1");
          for(int i=0;i<list1.size();i++)
          {
          Department department = list1.get(i);
           %>
           <option ><%=department.getDepartmentName() %></option>
           <%} %>
        </select> </tr>
      <tr>
        <td height="50" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">职务名称</span></div></td>
        <td height="50" bgcolor="#FFFFFF"><input type="text" name="positionname" id="positionname" class="STYLE2" onblur="checkName()"/>
        <span id="positionnameerror"></span></tr>
     <tr>
	 
        <td height="5" bgcolor="#FFFFFF" colspan="2"><div align="center">
          <p align="center"><input type="submit"  name="添加"  value="&nbsp;&nbsp;&nbsp;添加" class="button"/>
             <input type="reset"   name="重置"  value="&nbsp;&nbsp;&nbsp;重置" class="button"/>
          </p>
		</div>
       </td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
  </body>
</html>
