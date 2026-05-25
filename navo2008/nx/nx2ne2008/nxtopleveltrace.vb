Imports System.IO
Imports System.Diagnostics
Imports System.Runtime.InteropServices
Imports nxappcore

<ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_topleveltrace)> _
Public Class nxtopleveltrace
    Inherits nxtrace
    Sub New(ByVal oTraceManager As nxtrace_manager, ByVal strTraceName As String, _
        ByVal oSinkStreamObj As Object, ByVal oDOC_ As Object)
        MyBase.New(oTraceManager, Nothing, strTraceName, _
            create_stream_writer(oSinkStreamObj), "", True)
        m_oDOC_ = oDOC_
        m_bNotified = False
        oTraceManager.on_trace_started(Me)
    End Sub

    Public Function reinit(ByVal oSinkStreamObj As Object) As Object
        Dim oStream As Object = get_stream_writer().BaseStream
        write_finishing_sequence()
        get_stream_writer().Flush()
        get_stream_writer().Close()
        reset_counters()
        m_oSinkStreamWriter = create_stream_writer(oSinkStreamObj)
        m_bNotified = False
        write_starting_sequence()
        Return oStream.IStream
    End Function

    Public Overrides Sub on_event(ByVal eEvent As eInfoClass, ByVal strCode As String, ByVal strText As String)
        MyBase.on_event(eEvent, strCode, strText)

        '-------
        'notify NE2002 engine
        '-------
        If Not m_bNotified Then
            If Not m_oDOC_ Is Nothing Then
                m_oDOC_.postcommand("vn1001=9008 vn5000=7 vs5002='Dostêpne s¹ nowe komunikaty...' vn5001=0")
            End If
            m_bNotified = True
        End If
    End Sub

    Private m_oDOC_ As Object
    Private m_bNotified As Boolean
End Class
