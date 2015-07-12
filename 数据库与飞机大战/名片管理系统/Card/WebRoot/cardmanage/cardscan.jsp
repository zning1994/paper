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
<title>名片管理</title>
<link href="css/style5.css" rel="stylesheet" type="text/css" />
<link href="css/table.css" rel="stylesheet" type="text/css" />
	<script language="javascript" src="datepicker/WdatePicker.js"></script>
	<script language="javascript" src="js/card.js"></script>
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
  <form id="form1" name="form1" method="post" action="CardSelectServlet.action">
  <p class="STYLE8" align="center">查询名片<br />  
  </p>
  <table width="650" height="100" border="1" class="gridtable">
    <tr>
      <td class="STYLE1">创建时间</td>
      <td class="STYLE1">
			从
			<input type="text" name="date1" onFocus="WdatePicker()" />
			到<input type="text" name="date2" onFocus="WdatePicker()" />
			</td>
    </tr>
    <tr>
      <td width="30%">
      </td>
      <td width="70%">
      <select name="condition">
      <option value="1">按姓名</option>
      <option value="2">按公司名称</option>
      <option value="3">按部门名称</option>
      <option value="4">按职务名称</option>
      </select>
      <div id="suggest" style="display:none"></div>
      <input type="text" name="search" id="title"/></td>
    </tr>
    <tr>
      <td class="STYLE1">
                  共享权限
      </td>
      <td>
      <select name="share">
      <option value="1" selected>全部共享</option>
      <option value="2">公司内共享</option>
      <option value="3">部门内共享</option>
      </select>
      </td>
    </tr>
    <tr>
        <td height="15" bgcolor="#FFFFFF" colspan="2"><div align="center">
          <p>
            <input type="submit" name="查询" value="查询" id="button">
          </p>
		</div>       
		</td>
      </tr>
  </table>
  </form>
  <%
        List<Card> list =(List<Card>) session.getAttribute("cardlist");
        int size;
		  if (list == null) {
			size = 0;
			return;
		  } else{
			size = list.size(); 
		 }%>
		 <br/><br/>
<form action="CardExcelServlet.action"  method="post" name="formscan" id="formscan" >
  <table width="650" border="1" class="gridtable" <%=size > 0 ? "style='display:table;'": "style='display:none;'"%>>
    <tr>
      <td width="10%" class="STYLE1">姓名</td>
      <td width="14%" class="STYLE1">所在公司</td>
      <td width="14%" class="STYLE1">所在部门</td>
      <td width="14%" class="STYLE1">所在职务</td>
      <td width="10%" class="STYLE1">创建者</td>
      <td width="14%" class="STYLE1">创建时间</td>
      <td width="13%" class="STYLE1">详细信息</td>
      <td width="15%" class="STYLE1"><input type="checkbox" id="all" name="all" onClick="select_all()"/>全选</td>
    </tr>
    <% 
    CardDao dao = new CardDaoImpl();
    Card_UsersDao cudao = new Card_UsersDaoImpl();
    CompanyDao cd = new CompanyDaoImpl();
    DepartmentDao dd = new DepartmentDaoImpl();
    PositionDao pd = new PositionDaoImpl();
    UsersDao ud = new UsersDaoImpl();
    Users_CardDao ucd = new Users_CardDaoImpl();
    for(int i=0;i<list.size();i++)
    {
        Card c = list.get(i);
        Card_Users cu = cudao.findById(c.getCardId());
        String company = cd.findById(cu.getCompanyId());
        String department = dd.findById(cu.getDepartmentId());
        String position = pd.findById(cu.getPositionId());
    %>
    <tr>
      <td class="STYLE1"><%=cu.getCardUsersName() %></td>
      <td class="STYLE1"><%=company %></td>
      <td class="STYLE1"><%=department %></td>
      <td class="STYLE1"><%=position %></td>
      <td class="STYLE1"><%=ud.findById(ucd.findByCardId(c.getCardId())) %></td>
      <td class="STYLE1"><%=c.getCreateTime().toLocaleString().split(" ")[0] %></td>
      <td class="STYLE1"><a href="CardInfoServlet?cardid=<%=c.getCardId() %>">查看</a></td>
      <td><input type="checkbox" name="delete" id="delete" value="<%=c.getCardId() %>"/></td>
    </tr>
    <%} %>
    <tr>
		<td colspan="8" class="STYLE1" align="left">
		<span >当前<%=session.getAttribute("pageNow") %>/<%=session.getAttribute("pageCount") %>页 数据总量<%=session.getAttribute("number") %></span><span>每页
		<input type="text" id="pageSize" name="pageSize" style="width:25px" value="10"/>条</span><input type="button" value="设置" onclick="SetNum()" width="40px">
		<a href="CardSelectServlet.action?pageNow=1">首页</a>
		<a href="CardSelectServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>">上一页</a>
		<a href="CardSelectServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>">下一页</a>
		<a href="CardSelectServlet.action?pageNow=<%=session.getAttribute("pageCount") %>">尾页</a><span>转到第</span><input type="text" name="jump" id="jump" style="width:25px" /><span>页</span><input type="button"  value="跳转" onClick="Jump()" width="40px"/></td>
	  </tr>
	  <tr>
	  <td colspan="8" align="center">
  <input type="button" value="批量导出名片信息" onClick="Daochu()"/></td>
  
	  </tr>
  </table>
  </form>
  
<%
session.removeAttribute("cardlist");
session.removeAttribute("pageNow");
session.removeAttribute("pageCount");
session.removeAttribute("number"); %>
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
