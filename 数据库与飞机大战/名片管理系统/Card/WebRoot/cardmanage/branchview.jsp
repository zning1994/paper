<%@ page language="java" import="java.util.*,com.manager.entity.*,java.util.List" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<%
	List<Company> comlist = (List)request.getAttribute("comlist");
	List<Department> delist  = (List)request.getAttribute("delist");
	List<Position> poslist= (List)request.getAttribute("poslist");

 %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>/cardmanage">
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<TITLE>部门视图</TITLE>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<STYLE type=text/css> 
{
	FONT-SIZE: 12px
}
#menuTree A {
	COLOR: #566984; TEXT-DECORATION: none
}
</STYLE>
<SCRIPT src="cardmanage/Left.files/TreeNode.js" type=text/javascript></SCRIPT>
<SCRIPT src="cardmanage/Left.files/Tree.js" type=text/javascript></SCRIPT>
<META content="MSHTML 6.00.2900.5848" name=GENERATOR>

  </head>
<body>  
 <TABLE height="100%" cellSpacing=0 cellPadding=0 width="100%">
  <TBODY>
    <TR>
      <TD width=10 height=29><IMG src="Left.files/bg_left_tl.gif"></TD>
      <TD 
    style="FONT-SIZE: 18px; BACKGROUND-IMAGE: url(images/bg_left_tc.gif); COLOR: white; FONT-FAMILY: system">所在公司</TD>
      <TD width=10><IMG src="Left.files/bg_left_tr.gif"></TD>
    </TR>
    <TR>
      <TD style="BACKGROUND-IMAGE: url(../images/bg_left_ls.gif)"></TD>
      <TD id=menuTree 
    style="PADDING-RIGHT: 10px; PADDING-LEFT: 10px; PADDING-BOTTOM: 10px; PADDING-TOP: 10px; HEIGHT: 100%; BACKGROUND-COLOR: white" 
    vAlign=top></TD>
      <TD style="BACKGROUND-IMAGE: url(../images/bg_left_rs.gif)"></TD>
    </TR>
    <TR>
      <TD width=10><IMG src="Left.files/bg_left_bl.gif"></TD>
      <TD style="BACKGROUND-IMAGE: url(../images/bg_left_bc.gif)"></TD>
      <TD width=10><IMG 
src="Left.files/bg_left_br.gif"></TD>
    </TR>
  </TBODY>
</TABLE>

<SCRIPT type=text/javascript>
var tree = null;
var root = new TreeNode('公司视图');

<% for(int j=0;j<comlist.size();j++)
	{%>

var fun<%=j%> = new TreeNode('<%=comlist.get(j).getCompanyName()%>');
root.add(fun<%=j%>);
<%	    for(int i=0;i<delist.size();i++)
        {
%>

<%           if((comlist.get(j).getCompanyId())==(delist.get(i).getCompanyId())||(comlist.get(j).getCompanyId()+"").equals(delist.get(i).getCompanyId()+""))
             {%>

               var fund<%=i%> = new TreeNode('<%=(delist.get(i).getDepartmentName())%>');
               fun<%=j%>.add(fund<%=i%>);
                 <%for(int k=0;k<poslist.size();k++)
                 {
                 	if(delist.get(i).getDepartmentId()==poslist.get(k).getDepartmentId()){%>
                 		var funp<%=k%> = new TreeNode('<%=poslist.get(k).getPositionName()%>');
                 		fund<%=i%>.add(funp<%=k%>);
                 
                 <%}}%>

<%}

}}%>










/*
var tree = null;
var root = new TreeNode('系统菜单');
var fun1 = new TreeNode('人事管理');
var fun2 = new TreeNode('机构管理', 'BranchMgr.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun1.add(fun2);
var fun3 = new TreeNode('部门管理', 'DepartmentMgr.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun1.add(fun3);
var fun4 = new TreeNode('员工管理', 'EmployeeMgr.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun1.add(fun4);
root.add(fun1);
var fun5 = new TreeNode('日程管理');
var fun6 = new TreeNode('我的日程', 'MySchedule.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun5.add(fun6);
var fun7 = new TreeNode('部门日程', 'DeptSchedule.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun5.add(fun7);
var fun8 = new TreeNode('我的便签', 'MyNote.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun5.add(fun8);
root.add(fun5);
var fun9 = new TreeNode('文档管理');
var fun10 = new TreeNode('文档管理', 'DocumentMgr.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun9.add(fun10);
var fun11 = new TreeNode('回收站', 'Recycler.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun9.add(fun11);
var fun12 = new TreeNode('文件搜索', 'FileSearch.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun9.add(fun12);
root.add(fun9);
var fun13 = new TreeNode('消息传递');
var fun14 = new TreeNode('消息管理', 'MessageMgr.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun13.add(fun14);
var fun15 = new TreeNode('信箱', 'MailBox.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun13.add(fun15);
root.add(fun13);var fun16 = new TreeNode('系统管理');
var fun17 = new TreeNode('角色管理', 'RoleMgr.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun16.add(fun17);
var fun18 = new TreeNode('登录日志', 'LoginLog.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun16.add(fun18);
var fun19 = new TreeNode('操作日志', 'OperationLog.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun16.add(fun19);
var fun20 = new TreeNode('菜单排序', 'MenuSort.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun16.add(fun20);
root.add(fun16);
var fun21 = new TreeNode('考勤管理');
var fun22 = new TreeNode('签到签退', 'SignInOrOut.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun21.add(fun22);
var fun23 = new TreeNode('考勤查询', 'HistoryQuery.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun21.add(fun23);
var fun24 = new TreeNode('考勤统计', 'TimeStatistics.aspx', 'tree_node.gif', null, 'tree_node.gif', null);
fun21.add(fun24);
root.add(fun21);
tree = new Tree(root);
tree.show('menuTree')*/
tree = new Tree(root);
tree.show('menuTree');
</SCRIPT>

</body>
</html>
