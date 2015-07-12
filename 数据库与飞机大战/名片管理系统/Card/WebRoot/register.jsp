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
	<script type="text/javascript" language="javascript" src="js/left.js" charset="gbk"></script>
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
  <form action="" method="post" name="formregister" id="formregister">
    <div id="right_font"><img src="images/main_14.gif"/> 您现在所在的位置：首页 → <strong>用户注册信息</strong> </div>
    <%
    List<Register> list = (List<Register>)session.getAttribute("registerall"); 
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
                    <td class="STYLE1"><div align="center"></div></td>
                    <td class="STYLE1"><div align="center"></div></td>
                  </tr>
              </table></td>
              <td width="60">&nbsp;</td>
              <td width="60"><table width="90%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center"></div></td>
                    <td class="STYLE1"><br></td>
                  </tr>
              </table></td>
              <td width="80"><table width="88%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center">
                        <input type="checkbox" name="checkboxall" value="checkbox" onClick="select_all()"/>
                    </div></td>
                    <td class="STYLE1"><div align="center">全部通过</div></td>
                  </tr>
              </table></td>
              <td width="100"><table width="88%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center">
                        <input type="checkbox" name="checkboxno" value="checkbox" onClick="select_no()"/>
                    </div></td>
                    <td class="STYLE1"><div align="center">全部不通过</div></td>
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
		<td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">审核成功</span></strong></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><strong><span class="STYLE1">审核失败</span></strong></div></td>
      </tr>
      <%
                CompanyDao cd = new CompanyDaoImpl();
                DepartmentDao dd = new DepartmentDaoImpl();
                PositionDao pd = new PositionDaoImpl();
                int j=0,k=0;
                for(int i=0;i<list.size();i++)
                {
                      Register register = list.get(i);
                      String company = cd.findById(register.getRegisterCompanyId());
                      String department = dd.findById(register.getRegisterDepartmentId());
                      String position = pd.findById(register.getRegisterPositionId());
      %>
      <tr>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=register.getRegisterName() %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=company %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=department %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=position %></span></div></td>
        <td height="22" bgcolor="#FFFFFF"><div align="center"><span class="STYLE3"><%=register.getRegisterEmail() %></span></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><input type="checkbox" name="success"  value="<%=register.getRegisterId() %>" /></div></td>
		<td height="22" bgcolor="#FFFFFF"><div align="center"><input type="checkbox" name="failure"  value="<%=register.getRegisterId() %>"/></div></td>
      </tr>
      <%} %>
    </table></td>
  </tr>
  <tr>
    <td height="35"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="25%" height="29" nowrap="nowrap"><table width="602" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="22%" class="STYLE1">当前页：<%=session.getAttribute("pageNow") %>/<%=session.getAttribute("pageCount") %>页 每页<input name="pageSize" id="pageSize" type="text" class="STYLE1" style="height:20px; width:20px;" size="5" />            </td>
            <td width="9%" class="STYLE1"><img src="images/sz.gif" width="43" height="20" onClick="SetNum()"/></td>
            <td width="69%" class="STYLE1"><span class="STYLE7">数据总量<%=session.getAttribute("number") %> </span></td>
          </tr>
        </table></td>
        <td><div margin-left="300px"><table table width="150" border="0" cellspacing="0" cellpadding="0"><tr>
        <td width="14%" class="STYLE1"><img src="images/check_success.jpg" width="60" height="20" name="checksuccess" onClick="CheckSuccess()" /></td>
        <td width="14%" class="STYLE1"><img src="images/check_fail.jpg" width="60" height="20" name="checkfail" onClick="CheckFail()"/></td>
        </tr></table></div></td>
        <td width="75%" valign="top" class="STYLE1"><div align="right">
            <table width="352" height="20" border="0" cellpadding="0" cellspacing="0">
              <tr>
                <td width="62" height="22" valign="middle"><div align="right"><a href="RegisterSelectAllServlet.action?pageNow=1"><img src="images/page_first_1.gif" width="48" height="20" /></a></div></td>
                <td width="50" height="22" valign="middle"><div align="right"><a href="RegisterSelectAllServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>"><img src="images/page_back_1.gif" width="55" height="20" /></a></div></td>
                <td width="54" height="22" valign="middle"><div align="right"><a href="RegisterSelectAllServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>"><img src="images/page_next.gif" width="58" height="20"/></a></div></td>
                <td width="49" height="22" valign="middle"><div align="right"><a href="RegisterSelectAllServlet.action?pageNow=<%=session.getAttribute("number") %>"><img src="images/page_last.gif" width="52" height="20"/></a></div></td>
                <td width="59" height="22" valign="middle" class="STYLE1"><div align="right">转到第</div></td>
                <td width="25" height="22" valign="middle"><span class="STYLE7">
                  <input name="jump" id="jump" type="text" class="STYLE1" style="height:20px; width:25px;" size="5" />
                </span></td>
                <td width="23" height="22" valign="middle" class="STYLE1">页</td>
                <td width="30" height="22" valign="middle"><img src="images/go.gif" width="26" height="20" onClick="Jump()"/></td>
              </tr>
            </table>
        </div></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
<table align="center" border="0px" id="result"
				<%=size == 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
				<tr>
					<td align="center" textcolor="red">
						没有用户注册！！！
					</td>
				</tr>
			</table>
  </body>
</html>
