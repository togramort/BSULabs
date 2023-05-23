package model;

public class JDBCConnectionException extends Exception {
    public JDBCConnectionException(String message) {
        super(message);
    }

    public JDBCConnectionException(String message, Throwable e) {
        super(message, e);
    }

    @Override
    public String getMessage() {
        return super.getMessage();
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }
}
