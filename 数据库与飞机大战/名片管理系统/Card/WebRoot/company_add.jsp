<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>添加公司</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<link href="css/main.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" language="javascript" src="js/company.js"
			charset="gbk"></script>
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
.STYLE10 {width:204px;height:26px;margin-left:25px;margin-right:160px;}
-->
</style>

  </head>
  
  <body>
   <div id="right_font"><img src="images/main_14.gif"/> 您现在所在的位置：首页 →企业管理 →添加新公司 </div>
   <form action="CompanyAddServlet.action" method="post" onSubmit="return Check()">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <th  align="center"><p class="STYLE8">添加公司</p>
    </th>
  </tr>
  <tr>
    <td><table width="52%" height="322" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9" align="center">
     
        <td width="25%" height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">公司名称</span></div></td>
          <td width="68%" height="22" bgcolor="#FFFFFF"><input type="text" name="companyname" id="companyname" class="STYLE2" onblur="checkName()"/>
          <span id="companynameerror"></span>
        </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">公司地址</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><input type="text" name="address" id="address1" class="STYLE2" onblur="checkAddress()" margin-right="0px"/>
        <span id="companyaddresserror"></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">公司电话</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><input type="text" name="tel" id="tel"  class="STYLE2" onblur="checkTel()"/>
        <span id="companytelerror"></span>      </tr>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1">公司传真</span></div></td>
        <td height="22" bgcolor="#FFFFFF"><input type="text" name="fax" id="fax" class="STYLE2" onblur="checkFax()"/>
        <span id="companyfaxerror"></span>      </tr>
     <tr>
        <td height="22" align="center" bgcolor="#FFFFFF" colspan="2"><div align="center">
          <p align="center">
            <input type="submit"  name="添加"  value="添加" class="button"/>
            <input type="reset"   name="重置"  value="重置" class="button"/>
          </p>
		</div>       </td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
  </body>
</html>
