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
<title>无标题文档</title>
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
  
  <body background="images/backgraund.jpg">
<div align="center">

<form action="GroupAlterServlet.action" method="post" >
<p class="STYLE8">修改组<br />  
  </p>
  <% 
   Groups g = (Groups)session.getAttribute("groupitem");
   GroupDao dao = new GroupDaoImpl();
   String fatherName = "";
   if(g.getFatherGroupId()!=0){
    	fatherName = dao.findById(g.getFatherGroupId());
   }
   %>
<table width="600" border="1" class="gridtable" >
  <tr>
    <td width="87" class="STYLE1">组名</td>
    <td width="294"><input type="text" name="groupname" id="groupname" onblur="CheckName1()" value="<%=g.getGroupName() %>"/>
    <span id="groupnameerror" class="STYLE1"></span></td>
    <input type="text" name="oldgroupname" id="oldgroupname" value="<%=g.getGroupName() %>" style="display:none"/>
  </tr>
  <tr>
    <td class="STYLE1">所在父组</td><td>
    		<select name="fathername">
             <option><%=fatherName %></option>
    		<%
    		    List<Groups> list = dao.find("select * from groups where groupId not in (select groupId from groups where groupName='"+g.getGroupName()+"' or groupName='"+fatherName+"')");
    		    for(int i=0;i<list.size();i++)
    		    {
    		    	Groups c = list.get(i);
    		%>
    		 <option><%=c.getGroupName() %></option>
    		 <%} %>
            </select>
</td>
  </tr>
  <tr>
    <td class="STYLE1">简介</td>
    <td><textarea cols="50" row="5" name="note" id="note"><%=g.getNotes() %></textarea></td>
  </tr>
  <tr>
    <td class="STYLE1">查看权限：</td>
    <td><select name="share">
    <%if(g.getSharing()==1){ %>
      <option value="1" selected>全部共享</option>
      <option value="2">公司共享</option>
      <option value="3">部门共享</option>
    <%} else if(g.getSharing()==2){ %>
    <option value="2" selected>公司共享</option>
      <option value="1">全部共享</option>
      <option value="3">部门共享</option>
    <%} else if(g.getSharing()==3){ %>
     <option value="3" selected>部门共享</option>
      <option value="1">全部共享</option>
      <option value="2">公司共享</option>
    <%}%>
      </select>
      </td>
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
</div>
</body>
</html>
