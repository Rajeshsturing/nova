Imports System
Imports System.IO
Imports System.Runtime.InteropServices
Imports System.Runtime.InteropServices.ComTypes

Namespace Global.nxm.system.interop
    Public Class StreamOverIStream
        Inherits Stream

        Public Sub New(ByVal stream As IStream)
            m_stream = stream
        End Sub

        Public Overrides ReadOnly Property CanRead As Boolean
            Get
                Return True
            End Get
        End Property

        Public Overrides ReadOnly Property CanSeek As Boolean
            Get
                Return True
            End Get
        End Property

        Public Overrides ReadOnly Property CanWrite As Boolean
            Get
                Return True
            End Get
        End Property

        Public Overrides ReadOnly Property Length As Long
            Get
                Dim stat As System.Runtime.InteropServices.ComTypes.STATSTG
                m_stream.Stat(stat, 1)
                Return stat.cbSize
            End Get
        End Property

        Public Overrides Property Position As Long
            Get
                Dim ptr = Marshal.AllocHGlobal(8)
                Try
                    m_stream.Seek(0, CInt(SeekOrigin.Current), ptr)
                    Return Marshal.ReadInt64(ptr)
                Finally
                    Marshal.FreeHGlobal(ptr)
                End Try
            End Get
            Set(value As Long)
                Seek(value, SeekOrigin.Begin)
            End Set
        End Property

        Public Overrides Sub Flush()
            m_stream.Commit(0)
        End Sub

        Public Overrides Function Read(buffer() As Byte, offset As Integer, count As Integer) As Integer
            Dim temp(count - 1) As Byte
            Dim ptr = Marshal.AllocHGlobal(4)
            Try
                m_stream.Read(temp, count, ptr)
                Dim bytesRead = Marshal.ReadInt32(ptr)
                Array.Copy(temp, 0, buffer, offset, bytesRead)
                Return bytesRead
            Finally
                Marshal.FreeHGlobal(ptr)
            End Try
        End Function

        Public Overrides Function Seek(offset As Long, origin As SeekOrigin) As Long
            Dim ptr = Marshal.AllocHGlobal(8)
            Try
                m_stream.Seek(offset, CInt(origin), ptr)
                Return Marshal.ReadInt64(ptr)
            Finally
                Marshal.FreeHGlobal(ptr)
            End Try
        End Function

        Public Overrides Sub SetLength(value As Long)
            m_stream.SetSize(value)
        End Sub

        Public Overrides Sub Write(buffer() As Byte, offset As Integer, count As Integer)
            Dim temp(count - 1) As Byte
            Array.Copy(buffer, offset, temp, 0, count)
            m_stream.Write(temp, count, IntPtr.Zero)
        End Sub

        Private ReadOnly m_stream As IStream
    End Class

    Public Class CurrencyWrapper
        Public Sub New(ByVal value As Decimal)
            m_value = value
        End Sub

        Public Shared Widening Operator CType(ByVal wrapper As CurrencyWrapper) As Decimal
            Return wrapper.m_value
        End Operator

        Public Overrides Function ToString() As String
            Return m_value.ToString()
        End Function

        Private ReadOnly m_value As Decimal
    End Class
End Namespace
