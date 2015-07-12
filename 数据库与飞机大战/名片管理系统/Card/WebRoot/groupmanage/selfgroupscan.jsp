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
	<title>组管理页面</title>
	<link href="css/style4.css" rel="stylesheet" type="text/css" />
	<link href="css/table.css" rel="stylesheet" type="text/css" />
	<script language="javascript" src="datepicker/WdatePicker.js"></script>
	<script language="javascript" src="js/group.js"></script>
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
 <div  style="left:150px;" align="center">
 <form id="formself" name="formself" action="GroupDeleteServlet.action" method="post">
  <p class="STYLE8">个人组信息<br />  
  </p>
  <%
        List<Groups> list =(List<Groups>) session.getAttribute("selfgrouplist");
        int size;
		  if (list == null) {
			size = 0;
			return;
		  } else{
			size = list.size(); 
		 }%>
  <table width="650" border="1" class="gridtable" <%=size > 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
    <tr>
      <td width="15%" class="STYLE1">组名</td>
      <td width="15%" class="STYLE1">所在父组</td>
      <td width="15%" class="STYLE1">创建时间</td>
      <td width="12%" class="STYLE1">详细信息</td>
      <td width="10%" class="STYLE1"><input type="checkbox" id="all" name="all" onClick="select_all()"/>全选</td>
    </tr>
    <% 
    GroupDao dao = new GroupDaoImpl();
    for(int i=0;i<list.size();i++)
    {
           Groups g = list.get(i); 
    %>
    <tr>
      <td class="STYLE1"><%=g.getGroupName() %></td>
      <%if(g.getFatherGroupId()!=0){ %>
      <td class="STYLE1"><%=dao.findById(g.getFatherGroupId()) %></td>
      <%} else {%>
      <td class="STYLE1"></td>
      <%} %>
      <td class="STYLE1"><%=g.getCreateTime().toLocaleString().split(" ")[0] %></td>
      <td class="STYLE1"><a href="GroupInfoServlet.action?self=1&&groupid=<%=g.getGroupId() %>">查看</a></td>
      <td><input type="checkbox" name="delete" value="<%=g.getGroupId() %>"/></td>
    </tr>
    <%} %>
    <tr>
		<td colspan="6" class="STYLE1" align="left">
		<span >当前<%=session.getAttribute("pageNow") %>/<%=session.getAttribute("pageCount") %>页 数据总量<%=session.getAttribute("number") %></span><span>每页
		<input type="text" id="pageSize" name="pageSize" style="width:25px" value="10"/>条</span><input type="button" value="设置" onclick="SetNum1()" width="40px">
		<a href="GroupSelfServlet.action?pageNow=1">首页</a>
		<a href="GroupSelfServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>">上一页</a>
		<a href="GroupSelfServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>">下一页</a>
		<a href="GroupSelfServlet.action?pageNow=<%=session.getAttribute("pageCount") %>">尾页</a><span>转到第</span><input type="text" name="jump" id="jump" style="width:25px" /><span>页</span><input type="button"  value="跳转" onClick="Jump1()" width="40px"/></td>
	  </tr>
	  <tr>
	  <td colspan="6" align="center"><input type="button" value="删除" onClick="Delete()"/>
  <input type="button" value="导出组信息" onClick="Daochu1()"/>
  </td>
	  </tr>
  </table>
  
</form>
<%session.removeAttribute("grouplist");
session.removeAttribute("pageNow");
session.removeAttribute("pageCount");
session.removeAttribute("number");%>
<table align="center" border="0px" id="result"
				<%=size == 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
				<tr>
					<td align="center" textcolor="red">
						没有结果！！！
					</td>
				</tr>
			</table>
</div>
  </body>
</html>
