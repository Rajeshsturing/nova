Imports System.Runtime.InteropServices
Imports nxappcore

Namespace ne2002

    Public Class nxserialport
        Implements IDisposable

        Public Sub New()
            m_oNAVOPerifCom = CreateObject("navoperif.comobject")
            m_oTrace = Nothing
        End Sub
        Public Sub set_trace(ByVal oTrace As nxtrace)
            m_oTrace = oTrace
        End Sub
        Public WriteOnly Property port() As String
            Set(ByVal Value As String)
                m_oNAVOPerifCom.port = Value
            End Set
        End Property
        Public WriteOnly Property speed() As Integer
            Set(ByVal Value As Integer)
                m_oNAVOPerifCom.speed = Value
            End Set
        End Property
        Public WriteOnly Property parity() As Integer
            Set(ByVal Value As Integer)
                m_oNAVOPerifCom.parity = Value
            End Set
        End Property
        Public WriteOnly Property stopbits() As Integer
            Set(ByVal Value As Integer)
                m_oNAVOPerifCom.stopbits = Value
            End Set
        End Property
        Public WriteOnly Property bits() As Integer
            Set(ByVal Value As Integer)
                m_oNAVOPerifCom.bits = Value
            End Set
        End Property
        Public WriteOnly Property sink() As Object
            Set(ByVal Value As Object)
                m_oNAVOPerifCom.sink = Value
            End Set
        End Property
        Public ReadOnly Property lasterror() As Integer
            Get
                Return m_oNAVOPerifCom.error
            End Get
        End Property
        Public Sub Start()
            dbg_trace("nxserialport.start")

            m_oNAVOPerifCom.start()
        End Sub
        Public Sub write(ByVal iValue As Integer)
            dbg_trace("nxserialport.write iValue=" + iValue.ToString())

            m_oNAVOPerifCom.write(iValue)
        End Sub
        Public Sub writestr(ByVal strValue As String)
            dbg_trace("nxserialport.writestr strValue=" + strValue)

            m_oNAVOPerifCom.writestr(strValue)
        End Sub
        Public Sub writenow(ByVal strValue As String)
            writestr(strValue)
            flush()
        End Sub
        Public Sub flush()
            dbg_trace("nxserialport.flush")

            m_oNAVOPerifCom.flush()
        End Sub
        Public Sub fill(ByVal iCount As Integer)
            dbg_trace("nxserialport.fill iCount=" + iCount.ToString())

            m_oNAVOPerifCom.fill(iCount)
        End Sub
        Public Function read() As Integer
            Dim iReadChar As Integer = m_oNAVOPerifCom.read()
            If Not m_oTrace Is Nothing Then
                Dim cReadChar As Char : cReadChar = Chr(iReadChar)
                dbg_trace("nxserialport.read iReadChar=" + iReadChar.ToString() + "(" + cReadChar + ")")
            End If
            Return iReadChar
        End Function
        Private Sub dbg_trace(ByVal strTrace As String)
            If Not m_oTrace Is Nothing Then
                m_oTrace.info("DBG", strTrace)
            End If
        End Sub

        Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
            Dispose(True)
            GC.SuppressFinalize(Me)
        End Sub
        Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
            If Not m_oNAVOPerifCom Is Nothing Then
                If bDisposing Then
                    'noop
                End If
                m_oNAVOPerifCom.close()
            End If
            m_oNAVOPerifCom = Nothing
        End Sub
        Protected Overrides Sub Finalize()
            Dispose(False)
            MyBase.Finalize()
        End Sub

        Private m_oNAVOPerifCom As Object
        Private m_oTrace As nxtrace


    End Class
End Namespace