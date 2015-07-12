<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
<%@ page import="com.manager.entity.*,com.manager.dao.*,com.manager.dao.impl.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>用户管理界面</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<link href="css/main.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" language="javascript" src="js/user.js" charset="gbk"></script>
<style type="text/css">
<!--
.STYLE1 {font-size: 12px}
.STYLE3 {color: #707070; font-size: 12px; }
.STYLE5 {color: #0a6e0c; font-size: 12px; }
body {
	margin-top: 0px;
	margin-bottom: 0px;
}
.STYLE7 {font-size: 12}
-->
</style>

  </head>
  
  <body>
  <form action="DeleteUserServlet.action" method="post" name="formuser">
    <div id="right_font"><img src="images/main_14.gif"/> 您现在所在的位置：首页 → <strong>用户管理</strong> </div>
    <%
    List<Users> list =(List<Users>) session.getAttribute("userslist");
      List<Users_Position> list1 =(List<Users_Position>) session.getAttribute("users_position");
    int size;
		  if (list == null) {
			size = 0;
			return;
		  } else{
			size = list.size(); 
		 } %>
<table width="100%" border="0" cellspacing="0" cellpadding="0" <%=size > 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
  <tr>
    <td height="30"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td>&nbsp;</td>
        <td style="padding-right:10px;"><div align="right">
          <table border="0" align="right" cellpadding="0" cellspacing="0">
            <tr>
              <td width="60"><table width="87%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center">
                        <input type="checkbox" name="all" id="all"  value="checkbox" onClick="select_all()" />
                    </div></td>
                    <td class="STYLE1"><div align="center">全选</div></td>
                  </tr>
              </table></td>
              <td width="60"><table width="90%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center"><img src="images/select.png" width="14" height="14" onClick="Select()"/></div></td>
                    <td class="STYLE1"><div align="center" onClick="Select()">查询</div></td>
                  </tr>
              </table></td>
              <td width="52"><table width="88%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center"><img src="images/083.gif" width="14" height="14" onClick="Delete()"/></div></td>
                    <td class="STYLE1"><div align="center" onClick="Delete()">删除</div></td>
                  </tr>
              </table></td>
            </tr>
          </table>
        </div></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td><table width="100%" border="0" cellpadding="0" cellspacing="1" bgcolor="#c9c9c9">
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">用户名</span></strong></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">公司</span></strong></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">部门</span></strong></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">职务</span></strong></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">邮箱</span></strong></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">修改</span></strong></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">删除</span></strong></div></td>
      </tr>
      <%
      CompanyDao cd = new CompanyDaoImpl();
      DepartmentDao dd = new DepartmentDaoImpl();
      PositionDao pd = new PositionDaoImpl();
      for(int i=0;i<list1.size();i++){
      		Users_Position up = list1.get(i);
      		String company = cd.findById(up.getCompanyId());
            String department = dd.findById(up.getDepartmentId());
            String position = pd.findById(up.getPositionId());
            for(int j=0;j<list.size();j++){
            	Users u = list.get(j);
            	if(u.getUsersId()==up.getUsersId())
            	{
       %>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=u.getUsersName() %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=company %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=department %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=position %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=u.getEmail() %></span></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE1"><a href="#">修改</a></span></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><input type="checkbox" name="delete"  value="<%=u.getUsersId() %>"/></div></td>
      </tr>
      <%}}} %>
    </table></td>
  </tr>
  <tr>
    <td height="35"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="25%" height="29" nowrap="nowrap"><table width="342" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="44%" class="STYLE1">当前页：<%=session.getAttribute("pageNow") %>/<%=session.getAttribute("pageCount") %>页 每页 
              <input name="pageSize" id="pageSize" type="text" class="STYLE1" style="height:20px; width:25px;"  size="5" value="10"/>            </td>
            <td width="14%" class="STYLE1"><img src="images/sz.gif" width="43" height="20" onClick="SetNum()" /></td>
            <td width="42%" class="STYLE1"><span class="STYLE7">数据总量<%=session.getAttribute("number") %>  </span></td>
          </tr>
        </table></td>
        <td width="75%" valign="top" class="STYLE1"><div align="right">
            <table width="352" height="20" border="0" cellpadding="0" cellspacing="0">
              <tr>
                <td width="62" height="22" valign="middle"><div align="right"><a href="UserSelectServlet.action?all=1&&pageNow=1"><img src="images/page_first_1.gif" width="48" height="20" /></a></div></td>
                <td width="50" height="22" valign="middle"><div align="right"><a href="UserSelectServlet.action?all=1&&pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>"><img src="images/page_back_1.gif" width="55" height="20" /></a></div></td>
                <td width="54" height="22" valign="middle"><div align="right"><a href="UserSelectServlet.action?all=1&&pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>"><img src="images/page_next.gif" width="58" height="20" /></a></div></td>
                <td width="49" height="22" valign="middle"><div align="right"><a href="UserSelectServlet.action?all=1&&pageNow=<%=session.getAttribute("number") %>"><img src="images/page_last.gif" width="52" height="20" /></a></div></td>
                <td width="59" height="22" valign="middle" class="STYLE1"><div align="right">转到第</div></td>
                <td width="25" height="22" valign="middle"><span class="STYLE7">
                  <input name="jump" id="jump" type="text" class="STYLE1" style="height:20px; width:25px;" size="5" />
                </span></td>
                <td width="23" height="22" valign="middle" class="STYLE1">页</td>
                <td width="30" height="22" valign="middle"><img src="images/go.gif" width="26" height="20" onClick="Jump()" /></td>
              </tr>
            </table>
        </div></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
<%session.removeAttribute("userslist");
session.removeAttribute("users_position");
session.removeAttribute("pageNow");
session.removeAttribute("pageCount");
session.removeAttribute("number"); %>
<table align="center" border="0px" id="result"
				<%=size == 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
				<tr>
					<td align="center" textcolor="red">
						没有用户！！！
					</td>
				</tr>
			</table>
  </body>
</html>
