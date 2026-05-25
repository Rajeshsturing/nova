'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.Runtime.InteropServices
Imports System.IO
Public Class ne_connection
    Implements IDisposable

    Public Sub create(ByVal strApplication As String, ByVal strDBServer As String, ByVal strDBName As String, ByVal iUIStyle As Int32, ByVal bNXMTransport As Boolean)
        Trace("ne_connection.create start app=" & strApplication & " db=" & strDBName & " server=" & strDBServer & " ui=" & CStr(iUIStyle) & " nxm=" & CStr(bNXMTransport))
        Try
            Trace("CreateObject navo2002.client begin")
            m_oClient = CreateObject("navo2002.client")
            Trace("CreateObject navo2002.client ok null=" & CStr(m_oClient Is Nothing))

            Trace("client.document begin")
            m_oClientDoc = m_oClient.document
            Trace("client.document ok null=" & CStr(m_oClientDoc Is Nothing))

            Dim str As String = "vn1001=1030 vn1011=1 vn1002=72007 vn1016="

            str = str & CStr(iUIStyle)

            If bNXMTransport Then
                str = (str & " vs8080='nxm'")
            End If
            str = String.Concat(New String() {str, " vs8003='", strApplication, "' vs8008='", strDBName, "' vs1012='", strDBServer, "'"})

            Trace("callcommand begin " & str)
            m_oClientDoc.callcommand(str)
            Trace("callcommand ok")

            Trace("gettoppage begin")
            m_oTopPage = m_oClientDoc.gettoppage
            Trace("gettoppage ok null=" & CStr(m_oTopPage Is Nothing))
        Catch ex As Exception
            Trace("ne_connection.create exception " & ex.ToString())
            Throw
        End Try
    End Sub
    Public Sub Dispose() Implements IDisposable.Dispose
        Me.Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub

    Private Sub Dispose(ByVal bDisposing As Boolean)
        free_com_object(m_oTopPage)
        m_oTopPage = Nothing

        free_com_object(m_oClientDoc)
        m_oClientDoc = Nothing

        free_com_object(m_oClient)
        m_oClient = Nothing
    End Sub

    Protected Overrides Sub Finalize()
        Me.Dispose(False)
        MyBase.Finalize()
    End Sub
    Public Sub free_com_object(ByVal oComObject As Object)
        If (Not oComObject Is Nothing) Then
            Marshal.ReleaseComObject(oComObject)
        End If
    End Sub

    Public Function getmodule(ByVal iModule As Integer) As Object
        Return m_oClientDoc.getmodule(iModule)
    End Function

    Public Function createhli() As ne_property_set
        Return New ne_property_set(m_oClientDoc.createhli())
    End Function

    Private Shared Sub Trace(ByVal strMessage As String)
        Try
            Dim strPath As String = Environment.GetEnvironmentVariable("NAVO_COCOON_DIAG_LOG")
            If String.IsNullOrWhiteSpace(strPath) Then
                strPath = "C:\app\cocoon-diagnostics.log"
            End If
            File.AppendAllText(strPath, DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") & " [ne_connection] " & strMessage & Environment.NewLine)
        Catch
        End Try
    End Sub

    Private m_oClient As Object
    Private m_oClientDoc As Object
    Private m_oTopPage As Object
End Class

