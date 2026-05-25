Imports System.IO
Imports System.Text
Imports System.Xml
Imports System.Runtime.InteropServices
Imports nxappcore
Imports nxuibuilder
Imports nxuibuilder_control

Public MustInherit Class nxtracewriter_

    MustOverride Sub on_nxtrace_begin()
    MustOverride Sub on_nxtrace_end()
    MustOverride Sub on_starttag(ByVal strName As String, ByVal strDate As String)
    MustOverride Sub on_stoptag(ByVal strName As String, ByVal strDate As String, _
        ByVal iFatals As Integer, ByVal iErrors As Integer, _
        ByVal iWarnings As Integer, ByVal iInfos As Integer)
    MustOverride Sub on_fatal(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
    MustOverride Sub on_error(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
    MustOverride Sub on_warning(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
    MustOverride Sub on_info(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)

End Class

Public Class nxtrace_textwriter
    Inherits nxtracewriter_

    Public Sub New(ByVal oOutputStreamObj As Object, ByVal eMinInfoClass As nxtrace.eInfoClass)
        m_oSO = oOutputStreamObj
        m_iLevel = 0
    End Sub

    Public Overrides Sub on_fatal(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        m_oSO.write("!!")
        write_indent()
        m_oSO.write(strDate + " " + strCode + ":" + strText + vbCrLf)
    End Sub

    Public Overrides Sub on_error(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        m_oSO.write("! ")
        write_indent()
        m_oSO.write(strDate + " " + strCode + ":" + strText + vbCrLf)
    End Sub

    Public Overrides Sub on_warning(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        m_oSO.write("? ")
        write_indent()
        m_oSO.write(strDate + " " + strCode + ":" + strText + vbCrLf)
    End Sub

    Public Overrides Sub on_info(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        m_oSO.write("  ")
        write_indent()
        m_oSO.write(strDate + " " + strCode + ":" + strText + vbCrLf)
    End Sub

    Public Overrides Sub on_nxtrace_begin()
        m_oSO.write("-------------------------------------------------------" + vbCrLf)
        m_iLevel = m_iLevel + 1
    End Sub

    Public Overrides Sub on_nxtrace_end()
        m_iLevel = m_iLevel - 1
        m_oSO.write("-------------------------------------------------------" + vbCrLf)
    End Sub

    Public Overrides Sub on_starttag(ByVal strName As String, ByVal strDate As String)
        write_indent()
        m_oSO.write(strName + " (pocz¹tek:" + strDate + ")" + vbCrLf)
    End Sub

    Public Overrides Sub on_stoptag(ByVal strName As String, ByVal strDate As String, ByVal iFatals As Integer, ByVal iErrors As Integer, ByVal iWarnings As Integer, ByVal iInfos As Integer)
        write_indent()
        m_oSO.write(strName + " (zakoñczenie:" + strDate + ")" + vbCrLf)
    End Sub

    Private Sub write_indent()
        m_oSO.write(Space(m_iLevel + m_iLevel))
    End Sub
    Private m_oSO As Object
    Private m_iLevel As Integer

End Class

Public Class nxtrace_pagewriter
    Inherits nxtracewriter_

    Public Sub New(ByVal oOutputStreamObj As Object, ByVal eMinInfoClass As nxtrace.eInfoClass)
        m_oAspatorStack = New Stack

        m_oAspator = New aspator
        m_oAspator.init(oOutputStreamObj)
        m_oAspatorStack.Push(m_oAspator)

        m_oAspator.newtable.newsection("tbody", 1). _
           newgroup(table_row_group.eType.trg_flat, "").newrow().newcell()
    End Sub

 
    Public Overrides Sub on_nxtrace_begin()
        current_aspator().newrow.newcellex(1, "width='min'").newcellex(FORM_SPAN - 1, "")
        m_oAspatorStack.Push(current_aspator().newnestedaspator())
    End Sub

    Public Overrides Sub on_nxtrace_end()
        current_aspator().table = Nothing
        m_oAspatorStack.Pop()

        If m_oAspatorStack.Count = 1 Then
            m_oAspatorStack.Pop()
            m_oAspator.flush()
        End If
    End Sub

    Public Overrides Sub on_starttag(ByVal strName As String, ByVal strDate As String)
        'todo: rozpoznanie klasy
        Dim eClass As nxtrace.eInfoClass = nxtrace.eInfoClass.ic_info

        current_aspator().newtable.newsection("tbody", FORM_SPAN). _
             newgroupex(table_row_group.eType.trg_expandable_raport, strName + " (pocz¹tek: " + strDate + " )", _
                 "style='" + constants.STYLE_GROUP_HEADER.ToString() + "'" + attributes(eClass), _
                 (eClass > nxtrace.eInfoClass.ic_info))
    End Sub

    Public Overrides Sub on_stoptag(ByVal strName As String, ByVal strDate As String, ByVal iFatals As Integer, ByVal iErrors As Integer, ByVal iWarnings As Integer, ByVal iInfos As Integer)
        Dim eClass As nxtrace.eInfoClass = nxtrace.eInfoClass.ic_info
        Dim strMsg As String = ""

        If iFatals > 0 Then
            eClass = nxtrace.eInfoClass.ic_fatal
        Else
            If iErrors > 0 Then
                eClass = nxtrace.eInfoClass.ic_error
            Else
                If iWarnings > 0 Then
                    eClass = nxtrace.eInfoClass.ic_warning
                End If
            End If
        End If
        If iFatals > 0 Then
            strMsg = strMsg + CStr(iFatals) + " b³êdy fatalne, "
        End If
        If iErrors > 0 Then
            strMsg = strMsg + CStr(iErrors) + " b³êdy, "
        End If
        If iWarnings > 0 Then
            strMsg = strMsg + CStr(iWarnings) + " ostrze¿enia, "
        End If
        strMsg = strMsg + CStr(iInfos) + " informacje(i) "
        current_aspator().row_group = Nothing
        current_aspator().newgroup(table_row_group.eType.trg_flat, ""). _
            newrowex("backcolor='#f0f0f0' " + attributes(eClass)).newcellex(FORM_SPAN, "width='min'"). _
             e_autolabel(strName + " (zakoñczono: " + strDate + ")" + vbCrLf + " Wyst¹pi³y: " + strMsg)
    End Sub
    Public Overrides Sub on_fatal(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        current_aspator().newrowex(attributes(nxtrace.eInfoClass.ic_fatal)).newcellex(1, "width='min'").c_label(strDate).c_label(strCode). _
            c_autolabel(strText)
    End Sub

    Public Overrides Sub on_error(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        current_aspator().newrowex(attributes(nxtrace.eInfoClass.ic_error)).newcellex(1, "width='min'").c_label(strDate).c_label(strCode). _
            c_autolabel(strText)
    End Sub

    Public Overrides Sub on_warning(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        current_aspator().newrowex(attributes(nxtrace.eInfoClass.ic_warning)).newcellex(1, "width='min'").c_label(strDate).c_label(strCode). _
            c_autolabel(strText)
    End Sub

    Public Overrides Sub on_info(ByVal strCode As String, ByVal strText As String, ByVal strDate As String)
        current_aspator().newrowex(attributes(nxtrace.eInfoClass.ic_info)).newcellex(1, "width='min'").c_label(strDate).c_label(strCode). _
            c_autolabel(strText)
    End Sub

    Private Function attributes(ByVal eClass As nxtrace.eInfoClass) As String
        Select Case eClass
            Case nxtrace.eInfoClass.ic_info
                Return ""
            Case nxtrace.eInfoClass.ic_warning
                Return "bold='true'"
            Case nxtrace.eInfoClass.ic_error
                Return "forecolor='red'"
            Case nxtrace.eInfoClass.ic_fatal
                Return "forecolor='red' bold='true'"
            Case Else
                Return ""
        End Select
    End Function

    Private Function current_aspator() As aspator
        Return m_oAspatorStack.Peek()
    End Function

    Private m_oAspator As aspator
    Private m_oAspatorStack As Stack

    Const FORM_SPAN = 4
End Class
<ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxtrace2page)> _
Public Class nxtrace2page

    Public Enum eFormat
        t2pf_nxp = 0   'NE page
        t2pf_txt = 1  'plain text
    End Enum
    Public Sub New(ByVal oOutputStreamObj As Object, ByVal eMinInfoClass As nxtrace.eInfoClass, _
        ByVal eOutputFormat As eFormat)

        If eOutputFormat = eFormat.t2pf_nxp Then
            m_oWriter = New nxtrace_pagewriter(oOutputStreamObj, eMinInfoClass)
        Else
            m_oWriter = New nxtrace_textwriter(oOutputStreamObj, eMinInfoClass)
        End If
    End Sub

    Public Sub OnElementStart(ByVal strTag As String, ByVal oAttribMap As Object)
        Select Case strTag
            Case "nxtrace"
                m_oWriter.on_nxtrace_begin()
            Case "start"
                m_strDate = oAttribMap.Get("timestamp")
            Case "stop"
                m_strDate = oAttribMap.Get("timestamp")
                m_iFatals = CLng(oAttribMap.Get("fatals"))
                m_iErrors = CLng(oAttribMap.Get("errors"))
                m_iWarnings = CLng(oAttribMap.Get("warnings"))
                m_iInfos = CLng(oAttribMap.Get("infos"))
            Case "fatal", "error", "warning", "info"
                m_strInfo1 = oAttribMap.Get("code")
                m_strDate = oAttribMap.Get("timestamp")
        End Select
        m_strLatTag = strTag
    End Sub
    Public Sub OnData(ByVal strValue As String)
        Select Case m_strLatTag
            Case "start"
                m_oWriter.on_starttag(strValue, m_strDate)
            Case "stop"
                m_oWriter.on_stoptag(strValue, m_strDate, m_iFatals, m_iErrors, m_iWarnings, m_iInfos)
            Case "fatal"
                m_oWriter.on_fatal(m_strInfo1, strValue, m_strDate)
            Case "error"
                m_oWriter.on_error(m_strInfo1, strValue, m_strDate)
            Case "warning"
                m_oWriter.on_warning(m_strInfo1, strValue, m_strDate)
            Case "info"
                m_oWriter.on_info(m_strInfo1, strValue, m_strDate)
        End Select
    End Sub
    Public Sub OnElementEnd(ByVal strTag As String)
        If strTag = "nxtrace" Then
            m_oWriter.on_nxtrace_end()
        End If
    End Sub

    Private m_oWriter As nxtracewriter_
    Private m_strLatTag As String
    Private m_strInfo1 As String
    Private m_iFatals As Integer
    Private m_iErrors As Integer
    Private m_iWarnings As Integer
    Private m_iInfos As Integer
    Private m_strDate As DateTime
End Class
