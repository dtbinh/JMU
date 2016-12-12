<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <title>Tutors@JMU - Help</title>
    </head>
    <body>
        <%
            try {
                Boolean isLoggedInNow
                        = ((Boolean) (session.getAttribute("loggedIn")));
                if (!isLoggedInNow.booleanValue() || isLoggedInNow == null) {
        %>    
        <jsp:include page='<%="../header/header.jsp"%>'/>
        <%
        } else {
        %>    
        <jsp:include page='<%="../header/login_header.jsp"%>'/>
        <%
            }
        } catch (NullPointerException e) {
        %>
        <jsp:include page='<%="../header/header.jsp"%>'/>
        <%
            }
        %>
        <div class="container" id="help-container">
            <h1>Help Page</h1>
            <p>This will contain all of the help information and tutorials</p>
            <button type="button" class="btn btn-default" onClick="history.go(-1);
                    return true;">Go Back</button>
        </div>
        <jsp:include page="../footer/footer.jsp" /> 
    </body>
</html>
