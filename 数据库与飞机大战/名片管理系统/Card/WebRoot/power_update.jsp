<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
<%@ page import="com.manager.dao.*,com.manager.dao.impl.*,com.manager.entity.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>修改权限</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<link rel="stylesheet" type="text/css" href="css/main.css">
	<script type="text/javascript" language="javascript" src="js/power.js" charset="gbk"></script>
	<style type="text/css">
<!--
.STYLE2 { width:150px; height:18px; margin-left:40px;margin-top:2px;margin-bottom:2px;}
.button{background: transparent url('images/button.jpg');     color: #444;     font-family:"Microsoft YaHei",微软雅黑,"MicrosoftJhengHei",华文细黑,STHeiti,MingLiu; font-weight:300;   height: 24px; margin-left:30px;  margin-right: 10px;     padding-right: 18px;      text-decoration: none; 
}
body {
	margin-top: 0px;
	margin-bottom: 0px;
}
.STYLE8 {
	font-size: 30px;
	font-weight:normal;
}
.STYLE9 {font-size: 10px}
.STYLE10 {font-size: 12px;}
-->
</style>

  </head>
  
  <body>
  <% Powers p = (Powers) session.getAttribute("alterpower"); %>
    <div id="right_font">&nbsp;<img src="images/main_14.gif"/> <span class="STYLE9">您现在所在的位置：首页 →用户管理 →修改权限</span> </div>
<form action="PowerAlterServlet.action" method="post" onSubmit="return Check()">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <th align="center"><p class="STYLE8">修改权限</p>
    </th>
  </tr>
  <tr>
    <td><span class="STYLE10"></span>
      <table width="70%" height="300" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9" align="center">
        <input type="text" name="powerId"  class="STYLE2" style="display:none" value="<%=p.getPowerId() %>"/>  
        <tr>
          <td width="60%" height="22" bgcolor="#FFFFFF"><div align="center" class="STYLE10">权限名</div></td>
          <td width="40%" height="22" bgcolor="#FFFFFF">
        <input type="text" name="powername" id="powername" class="STYLE2" value="<%=p.getPowerName() %>" onblur="checkName()"/>
        <span id="powernameerror"></span></tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有用户管理权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getUsersManager()==1){ %>
            <input  type="radio" name="user" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="user" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="user" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="user" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        </tr>
        
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有名片管理权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getCardManager()==1){ %>
            <input  type="radio" name="card" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="card" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="card" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="card" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有组管理权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getGroupManager()==1){ %>
            <input  type="radio" name="group" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="group" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="group"  value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="group" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
       </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有数据导出权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getDataOut()==1){ %>
            <input  type="radio" name="data" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="data" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="data"  value="1"/>
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="data" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有审核用户注册信息管理权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getCheckUsers()==1){ %>
            <input  type="radio" name="check" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="check" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="check" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="check" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有日志管理权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getLogManager()==1){ %>
            <input  type="radio" name="log" value="1" checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="log" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="log" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="log" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有参数管理权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getParameterManager()==1){ %>
            <input  type="radio" name="parameter" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="parameter" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="parameter" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="parameter" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有查询组权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getSelectGroup()==1){ %>
            <input  type="radio" name="select"  value="1" checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="select" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="select" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="select" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
       </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有添加组权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getAddGroup()==1){ %>
            <input  type="radio" name="add" value="1"  checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="add" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="add" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="add"  value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
       </tr> 
       <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有删除组权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getDeleteGroup()==1){ %>
            <input  type="radio" name="delete" value="1" checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="delete"  value="0"/> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="delete" value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="delete" value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
       </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有修改组权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getAlterGroup()==1){ %>
            <input  type="radio" name="alter" value="1" checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="alter" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="alter"  value="1"/>
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="alter"  value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
        </tr>
        <tr>
          <td height="28" bgcolor="#FFFFFF"><div align="center" class="STYLE10">是否具有向组中添加名片权限</div>		</td>
          <td height="28" bgcolor="#FFFFFF">
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <%if(p.getAddInGroup()==1){ %>
            <input  type="radio" name="addin"  value="1"checked />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="addin" value="0" /> 
            <span class="STYLE10">否   </span>
            <%} else {%>
            <input  type="radio" name="addin"  value="1" />
            <span class="STYLE10">是 </span>&nbsp;&nbsp;
            <input type="radio" name="addin"  value="0" checked /> 
            <span class="STYLE10">否   </span>
            <%} %>
      </tr>
      </table>
        <form id="form1" name="form1" method="post" action=""><div align="center">
          <label> <br />
            <br />
            <input type="submit" name="modify" value="&nbsp;&nbsp;修改" class="button"/>
          </label>
          <label>
            <input type="reset" name="back" value="&nbsp;&nbsp;重置"  class="button"/>
          </label>
      </form>
    <p>&nbsp;</p></td>
  </tr>
</table>
</form>
  </body>
</html>
